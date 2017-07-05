﻿// -*- mode:c++; coding:utf-8-ws -*-
#ifndef MY_CONFIG_H
#define MY_CONFIG_H

// clang-format off

/*
●やりたいこと.
- [?] 2015.6.5
  bug, カーソル移動したときに移動前の状態が一瞬残る
  \view\CEditView_Scroll.cpp:void CEditView::ScrollDraw() があやしい?
  ScrollWindowEx() で行われる更新をなんとかすればいい?

- [ ] 2015.7.2
  開いているタブのファイル名をコピー.

- [ ] 2015.8.4
  タスクバーアイコンのちらつき
  \window\CTabWnd.cpp:CTabWnd::ShowHideWindow()
  SendMessageTimeout() と TabWnd_ActivateFrameWindow() の関係

- [ ] 2017.1.10
  bug?, 画面上端下端でキャレットが消えたタイミングでスクロールさせるとキャレットが消えたままスクロールする

- [ ] 2017.3.3
  テキスト描画、文字の右端が欠ける
  [patchunicode:#588]をあてて目立たなくはしている, 続けて描画されれば欠けない
  [patchunicode:#860]をあてれば解消しそう
    sakura_core\view\CEditView_Paint.cpp
    pcFigureManager->GetTextFigure().DrawImp(pInfo, nPosBgn, pInfo->GetPosInLogic() - nPosBgn);

- [ ] 2017.4.4
  BkSpを押したときにタブ入力文字だけしかない場合は逆TABにする

- [x] 2017.5.13 , 2017.6.20 
  せっかくいろいろなデフォルトタイプがあるのだから任意のタイプを追加できるようにしたい

- [ ] 2017.6.7
  #RRGGBB を色付け

- [ ] 2017.6.11 
  空白タブ改行行番号の表示切替

- [x] 2017.6.11 , 2017.6.20 
  Grep, Exclude dirsの追加、検索時に # をつけて「ファイル」につなげる
  Grep, 「$cpp」を「*.c *.cpp *.cc *.cxx *.c++ *.h *.hpp」などに展開する機能 
*/

// ● フォント
//   https://support.microsoft.com/ja-jp/kb/74299
//   http://d.hatena.ne.jp/itoasuka/20100104/1262585983
//
// lf.lfHeight = DpiPointsToPixels(-10); // 高DPI対応（ポイント数から算出）

// 修正者
#define UZ_AUTHOR       "Uzuki"
#define UZ_AUTHOR_PAGE  "https://github.com/uzuki3/sakura"

// 拡張用レジストリキー
#define UZ_REGKEY _T("Software\\sakura-uzuki")

//------------------------------------------------------------------
// バージョン情報ダイアログの変更 2017.3.15
//------------------------------------------------------------------
#define UZ_FIX_VERDLG
	#define PR_VER      2,43,0,0
	#define PR_VER_STR "2.43"
	#define BASE_REV    4190

//-------------------------------------------------------------------------
// デバッグ用
//-------------------------------------------------------------------------

// デバッグ出力 2015.3.24
//#define UZ_OUTPUT_DEBUG_STRING


//-------------------------------------------------------------------------
// 編集
//-------------------------------------------------------------------------

//------------------------------------------------------------------
// スクロール
//------------------------------------------------------------------
#define UZ_FIX_SCROLL
	// 水平スクロールの変更
	//  - スクロール開始マージンを 1 に変更。画面の端でスクロール開始 2014.5.7
	//  - スクロール幅を 16 に設定。一度に大きく移動することで見やすくする (Imitate 'Notepad') 2015.9.2
	#define UZ_HORIZONTAL_SCR (16)
	// 垂直スクロールの変更
	//  - スクロールマージンを 0 に変更 2017.4.9
	#define UZ_VERTICAL_SCR (0)

//------------------------------------------------------------------
// カーソルが大きく移動する処理ではカーソル行をセンタリングする 2017.4.13
//  (行番号ジャンプやタグジャンプ、アウトライン解析から移動した場合など)
//  - 同一画面内の移動はセンタリングしない
//  ! CCaret::MoveCursor, 同期スクロールの対応がまだ
//------------------------------------------------------------------
#define UZ_FIX_CENTERING_CURSOR_JUMP

//------------------------------------------------------------------
// タブ入力文字の切り替え(タブ<->空白)を追加
//  - S_ChangeTabWidthマクロ修正, 負の値を渡すとタブ文字の切り替え
//------------------------------------------------------------------
#define UZ_FIX_CHANGE_TAB_WIDTH_MACRO


//-------------------------------------------------------------------------
// 表示
//-------------------------------------------------------------------------

//------------------------------------------------------------------
// UIフォント
//  - "ＭＳ Ｐゴシック" -> "MS Shell Dlg"
//  - .rcファイルは数が多いので置換対応
//------------------------------------------------------------------
#define UZ_FIX_UI_FONT

//------------------------------------------------------------------
// SetMainFontにポイントのオフセット引数を追加 2017.6.22 
//------------------------------------------------------------------
#define UZ_FIX_SETMAINFONT

//------------------------------------------------------------------
// 'BOM付' を 'BOM' に変更 2017.4.17
//  - わざわざ「付」をつけなくても認識できると判断とスペースの節約
//------------------------------------------------------------------
#define UZ_FIX_WITH_BOM_TEXT

//------------------------------------------------------------------
// タブ名カラー
//------------------------------------------------------------------
#define UZ_FIX_TAB_CAPTION_COLOR
	// 変更ドキュメントタブ名カラー
	// (REG/TabCaptionModifiedColor:#0000d7)
	#define UZ_MODIFIED_TAB_CAPTION_COLOR _T("#0000d7")
	// マクロ記録中ドキュメントタブ名カラー
	// (REG/TabCaptionRecMacroColor:#d80000)
	#define UZ_RECMACRO_TAB_CAPTION_COLOR _T("#d80000")

//------------------------------------------------------------------
// タブウィンドウ 2015.8.28
//  - ウィンドウまとめモードの切り替え時にスリープを10ms入れる(ちらつき抑制) 2017.4.6
//  - タブをダブルクリックで閉じる 2017.4.6 - 2017.4.7
//  - ウィンドウが非アクティブなどきに非アクティブタブを選択したらそのタブをアクティブにする 2017.4.13
//  - WM_LBUTTONDOWN でウィンドウをアクティブにするようにする (修正前は WM_LBUTTONUP) 2017.4.14
//    この修正の影響で非アクティブウィンドウのドラッグができなくなった (対応予定)
//  - 境界線を描画しない, タブを詰める
//  - タブを閉じるボタンをグラフィカルにする
//  - 間に選択タブがあると右側のエッヂがないバグを修正 (となりのタブが上書き描画していた)
//  ? 各ウィンドウのタブウィンドウは生成時に自身の位置が選択されている状態から始まる
//    オーダーが変わらない限り選択タブが変わることはない
//    ウィンドウ切り替え時に自身が選択されたタブウィンドウが表示されることでタブを切り替えたように表現しているだけ
//    そのためスクロール状態からの切り替え時にスクロール位置が同期していない
//------------------------------------------------------------------
#define UZ_FIX_TABWND

//------------------------------------------------------------------
// エディット画面 2017.4.28
//  - エディット画面のスタイルから WS_EX_STATICEDGE を外し境界線を描かないようにする
//    そのかわりにルーラー上部に COLOR_ACTIVEBORDER で境界線を描画する
//------------------------------------------------------------------
#define UZ_FIX_EDITVIEW

//------------------------------------------------------------------
// エディット画面 スクロールバー
//  - 検索結果を表示 2017.6.9 
//  - ブックマークを表示 2017.6.9 
//  - カーソル行を表示 2017.6.11 
//  - 結果を上に描画しているため現在の範囲がわかりにくい → スクロールバーのカラーとブレンドする 2017.6.14 
//  ? 更新がいまいち, バーにカーソルを乗せた時 → フェードアウトして消えてしまう;
//------------------------------------------------------------------
#define UZ_FIX_EDITVIEW_SCRBAR
	#define UZ_SCRBAR_FOUND_MAGIC (0x10000000)  // 検索
	#define UZ_SCRBAR_MARK_MAGIC  (0x20000000)  // ブックマーク
	#define UZ_SCRBAR_LINEN_MASK  (0x0fffffff)  // 行番号マスク
	#define UZ_SCRBAR_MAGIC_MASK  (0xf0000000)  // マジックマスク
	// 検索文字列のある行の色
	// (REG/EditViewScrBarFoundColor:#0000d7)
	#define UZ_SCRBAR_FOUND_COLOR  _T("#f4a721") // _T("#0000d7")
	// ブックマークのある行の色
	// (REG/EditViewScrBarMarkColor:#d80000)
	#define UZ_SCRBAR_MARK_COLOR   _T("#ff0000") //_T("#d80000")
	// キャレットのある行の色
	// (REG/EditViewScrBarMarkColor:#d80000)
	#define UZ_SCRBAR_CURSOR_COLOR _T("#0000cd") //_T("#00d800")

//------------------------------------------------------------------
// 行を中央ぞろえにする 2014.3.26 - 2015.7.24
//  - デフォルトでは行は上揃えになっているので行間は下に付加される
//  x キャレットを行間含む高さにする
//------------------------------------------------------------------
#define UZ_LINE_CENTERING

//------------------------------------------------------------------
// EOFのみの行にも行番号を表示 2017.3.10
//------------------------------------------------------------------
#define UZ_FIX_EOFLN_DISP_NR

//------------------------------------------------------------------
// 半角空白文字
// - 半角空白文字を "・" で描画 (Imitate 'Sublime Text') 2013.6.2
// - Non-Breaking-Spaceを半角空白として表示する 2017.4.15
//------------------------------------------------------------------
#define UZ_FIX_HAN_SPACE

//------------------------------------------------------------------
// タブ文字（矢印）の鏃(>)は表示しない (Imitate 'Sublime Text') 2015.5.25
//  - 「長い矢印」「短い矢印」→「線」 2016.8.19
//  -> タブ表示の文字指定廃止, 表示は線のみ 2017.3.29
//------------------------------------------------------------------
#define UZ_FIX_TAB_MARK

//------------------------------------------------------------------
// カーソル行アンダーライン
//  - 左端から 2015.1.30
//------------------------------------------------------------------
#define UZ_FIX_CUR_UL

//------------------------------------------------------------------
// 選択領域の色
//  - テキストと背景のブレンド率設定 2015.6.5
//  - 選択時のテキスト属性（太字、下線）に選択領域ではなく現在のテキストを使用する
//  - カラー設定は背景カラーのみ
//------------------------------------------------------------------
#define UZ_FIX_SELAREA
	// 選択領域のブレンド率[%] 2015.6.5
	// (REG/SelectAreaTextBlendPer:0x00000000)
	// (REG/SelectAreaBackBlendPer:0x00000064)
	// (REG/SelectAreaBackBlendPer2:0x0000003C)
	#define UZ_SELAREA_TEXT_BLEND_PER (0)
	#define UZ_SELAREA_BACK_BLEND_PER (100)  // 選択範囲のブレンド率
	#define UZ_SELAREA_BACK_BLEND_PER2 (60)  // 特定の下地のときの選択範囲のブレンド率

//------------------------------------------------------------------
// 空白,TAB,改行,EOF,ノート線のカラー (Imitate 'Sublime Text') 2015.6.5
//  - 現在のテキスト色と現在の背景色をブレンドする (空白TABのカラー設定は無効化されます) 2015.6.8
//    対象は空白TABなどで、コントロールコードには適用されません
//  - 空白,タブ,改行の色は他のカラー設定の影響を受けます
//------------------------------------------------------------------
#define UZ_FIX_WS_COLOR
	// 空白,TAB,改行,EOF,ノート線 現在のカラーのブレンド率[%] 2015.6.5
	// (REG/WhiteSpaceBlendPer:0x0000001E)
	#define UZ_WS_BLEND_PER (30)
//						     
						     

//------------------------------------------------------------------
// カラー設定 2016.6.25
//  - カーソル位置縦線 テキストカラーのみ
//  - 折り返し記号 テキストカラーのみ
//------------------------------------------------------------------
#define UZ_FIX_COLOR_STRATEGY

//------------------------------------------------------------------
// コメント行 2016.12.27
// 0x01: 改行以降もカラーを有効にする (Imitate 'Sublime Text')
//------------------------------------------------------------------
#define UZ_FIX_COMMENT

//------------------------------------------------------------------
// 数値の色付け判定
//  - 正規表現で判定する 2017.4.21
//------------------------------------------------------------------
#define UZ_FIX_NUMERIC_COLOR

//------------------------------------------------------------------
// ステータスバー 2015.6.10 - 2017.4.1, 2017.6.11 
//  - ちらつき抑制
//  - カラムの並べ替え
//  - 左クリックでモード切り替えメニューを表示
//  - 「? 行 ? 桁」→「Ln ?, Col ?」に変更
//  - タイプ名を表示 (左クリック: メニュー表示)
//  - タブサイズを表示 (左クリック: メニュー表示)
//  - 入力改行コードを主に使われているシステム名で表記
//------------------------------------------------------------------
#define UZ_FIX_STATUSBAR

//------------------------------------------------------------------
// 折り返しモード 2017.6.3
//  - トグルで切り替えたときに「折り返さない」が処理されていないので修正
//------------------------------------------------------------------
#define UZ_FIX_WRAP_MODE

//-------------------------------------------------------------------------
// 機能
//-------------------------------------------------------------------------

//------------------------------------------------------------------
// Luaを使用する
//------------------------------------------------------------------
#define UZ_USE_LUA

//------------------------------------------------------------------
// PPAを使用する
//  - 64bit版のときはPPAの処理を無効にする
//------------------------------------------------------------------
#ifndef _WIN64
#define UZ_USE_PPA
#endif

//------------------------------------------------------------------
// プロファイル
//  - 起動時に存在しないファイル・フォルダの履歴は削除する 2017.4.10
//    (REG/DeleteHistoryNotExistAtStartup:1)
//  - 履歴は別ファイルで扱う (sakura.recent) 2017.5.2
//  - カラー設定のインポートはカラー情報だけを適用させる 2017.5.4
//  - カラー設定の色に名前を付ける (fg,bg,white,blackなど) 2017.5.10
//  - sakura.keywordset.csvを用意し、強調キーワードの管理はこのファイルで行う 2017.5.13
//  - プライグインの設定書き込み時、未定義値を無視する 2017.6.12 
//  - 印刷設定書き込み時、未定義値を無視する 2017.6.12 
//------------------------------------------------------------------
#define UZ_FIX_PROFILES
	#define UZ_DELETE_HISTORY_NOT_EXIST_AT_STARTUP (1)

//------------------------------------------------------------------
// メインメニューはデフォルトを使用する 2017.5.15
//  - 共通設定から「メインメニュー」タブを削除します
//------------------------------------------------------------------
#define UZ_FIX_MAINMENU_FORCE_DEFAULT

//------------------------------------------------------------------
// 開かれているファイルを自己管理する前提で多重オープンの許可 2013.6.19
//  - Shiftを押しながらファイルドロップで多重オープン
//------------------------------------------------------------------
#define UZ_MULTIPLE_OPEN_FILES

//------------------------------------------------------------------
// 最大数 2013.10.2, 2016.12.13, 2017.6.18 
// \sakura_core\config\maxdata.h
// (REG/RecentSearchKeyMax:20)
// (REG/RecentReplaceKeyMax:20)
// (REG/RecentGrepFileMax:10)
// (REG/RecentGrepFolderMax:20)
//------------------------------------------------------------------
#define UZ_FIX_MAXDATA
	#define UZ_MAX_SEARCHKEY  (20) // 検索キー
	#define UZ_MAX_REPLACEKEY (20) // 置換キー
	#define UZ_MAX_GREPFILE   (10)  // Grepファイル
	#define UZ_MAX_GREPFOLDER (20) // Grepフォルダ

//------------------------------------------------------------------
// メニューアイコン
//  - ビットマップメニュー
//      ::InsertMenuItem( hMenu, 0xFFFFFFFF, TRUE, &mii );
//      http://home.a00.itscom.net/hatada/windows/introduction/menu01.html
//      http://eternalwindows.jp/winbase/menu/menu10.html
//    起動時にアイコンの数だけHBITMAPを生成する
//      \sakura_core\uiparts\CImageListMgr.cpp
//------------------------------------------------------------------
#define UZ_FIX_MENUICON

//------------------------------------------------------------------
// 最近使ったファイル
//  - ファイルパスを短縮して表示する 2017.6.15 
//    (REG/FilePathCompactLength:50)
//  - ファイルサイズを表示 2017.6.15 
// \sakura_core\env\CFileNameManager.cpp
//   bool CFileNameManager::GetMenuFullLabel(
// \sakura_core\recent\CMRUFile.cpp
//   HMENU CMRUFile::CreateMenu( HMENU	hMenuPopUp, CMenuDrawer* pCMenuDrawer ) const
// \sakura_core\window\CEditWnd.cpp
//   cMRU.CreateMenu( hMenu, &m_cMenuDrawer );	//	ファイルメニュー
//------------------------------------------------------------------
#define UZ_FIX_RECENT_FILE_DISP_NAME
	#define UZ_FILEPATH_COMPACT_LENGTH (50)

//------------------------------------------------------------------
// タイプ別設定一覧の「追加」から任意のタイプを追加できるようにする 2017.6.20 
//------------------------------------------------------------------
#define UZ_FIX_TYPELIST_ADD_ANY_TYPE

//------------------------------------------------------------------
// デフォルト文字コードを UTF8にする 2017.6.22 
//------------------------------------------------------------------
#define UZ_FIX_DEFAULT_CHARCODE_TO_UTF8

//------------------------------------------------------------------
// 正規表現検索の際、検索文字列の正規表現記号をクォートする 2015.6.1
// PHPの preg_quote みたいなもの
//------------------------------------------------------------------
#define UZ_FIX_SEARCH_KEY_REGEXP_AUTO_QUOTE

//------------------------------------------------------------------
// 検索
//  ! 検索履歴からのオートコンプリート
//------------------------------------------------------------------
//#define UZ_FIX_FIND

//------------------------------------------------------------------
// Grep 2015.8.24
//  - Grepするフォルダの指定を UI的に増やす (Imitate 'MIFES')
//    →カンマで区切るより分かれていた方が扱いやすいし、履歴管理もしやすい.
//  - 除外フォルダ指定を別ボックスで指定できるようにする 2017.6.18 
//  - 指定フォルダをすべてチェックをはずすと「現在編集中のファイルから検索」とする
//  - 「現在編集中のファイルから検索」をチェックした時の状態を保持しないようにする
//    →本来の「現在編集中のファイルから検索」を使用すると、
//      影響を受ける他のチェックボックスの状態が変更したまま戻らないのが嫌だから.
//  - ファイル(フィルタ)指定はフォルダのあとに置く (フォルダのほうが変更する機会が多いため)
//------------------------------------------------------------------
#define UZ_FIX_GREP

//------------------------------------------------------------------
// 置換 2016.8.4
//  - 置換後文字列に置換前文字列を設定する
//------------------------------------------------------------------
#define UZ_FIX_REPLACE

//------------------------------------------------------------------
// フォルダ選択ダイアログ 2015.8.25
//  - CLSID_FileOpenDialogを使用する
//    使用するには Vista以降にする必要がある
//      -  WINVER=0x0500;_WIN32_WINNT=0x0500;_WIN32_IE=0x0501
//      -> WINVER=0x0601;_WIN32_WINNT=0x0601;_WIN32_IE=0x0800
// http://eternalwindows.jp/installer/originalinstall/originalinstall02.html
// https://msdn.microsoft.com/ja-jp/library/windows/desktop/ff485843(v=vs.85).aspx
// http://qiita.com/hkuno/items/7b8daa37d9b68e390d7e _WIN32_WINNT
// http://www.02.246.ne.jp/~torutk/cxx/vc/vcpp100.html
//------------------------------------------------------------------
#define UZ_FIX_SELECTDIR

//------------------------------------------------------------------
// ダイアログを編集ウィンドウに配置 2017.4.4
//  - アウトライン解析
//  - 外部コマンド実行
//  - 検索
//  - 置換
//  - Grep
//  - Grep置換
//  - 指定行へジャンプ
//  - タグファイルの作成
//  - タグジャンプリスト
//  - ウィンドウ一覧表示
//  - 文字コードの指定
//  - 履歴とお気に入りの管理
//  - 更新通知及び確認
//  - 中断
//------------------------------------------------------------------
#define UZ_FIX_DIALOG_POS

//------------------------------------------------------------------
// タグジャンプ一覧
//  - 表示するカラムの選別と並び替え 2015.8.27
//------------------------------------------------------------------
#define UZ_FIX_TAGJUMP

//------------------------------------------------------------------
// ダイアログ
//  - コンボボックスのドロップダウンは上下キーでは行えないようにする(誤操作防止) 2017.7.4 
//    ドロップダウンさせるときは Alt+UpDown で行う
//------------------------------------------------------------------
#define UZ_FIX_DLG

//------------------------------------------------------------------
// タグファイル作成ダイアログ
//  - タグ作成フォルダの初期値を tags ファイルがあるところまで辿る 2017.5.12
//------------------------------------------------------------------
#define UZ_FIX_TAGMAKEDLG

//------------------------------------------------------------------
// アウトライン解析ダイアログ 2016.12.14
//  - フォントをメインフォントにする
//  - ドッキング時、ウィンドウカラーにシステムカラーを使う
//    (REG/OutlineDockSystemColor:1)
//  - アウトライン解析ダイアログツリーのテーマに 'Explorer' を使用する 2017.5.1
//  - ルールファイル解析で「デフォルト」だとソートしていないため逆順になる 2017.5.9
//------------------------------------------------------------------
#define UZ_FIX_OUTLINEDLG

//------------------------------------------------------------------
// 検索ダイアログ 
//  - 検索ダイアログを自動的に閉じないとき、インクリメンタル検索をする 2017.6.21 
//  - レイアウトをダイアログを開いたままでも邪魔にならないようにコンパクト化 2017.6.22 
//  - ダイアログにフォーカスがあるときも「次を検索」「前を検索」キーを使用できるようにする 2017.6.24 
//  - VisualStudioの検索を模倣 2017.6.24 
//------------------------------------------------------------------
#define UZ_FIX_FINDDLG

//------------------------------------------------------------------
// 検索ボックス (ツールバー) 
//  - インクリメンタル検索をする 2017.7.1 
//  - ダイアログにフォーカスがあるときも「次を検索」「前を検索」キーを使用できるようにする 2017.7.1 
//  - エスケープキーでエディット画面にフォーカスを戻す 2017.7.1 
//  ! こっちのほうが使い勝手が良ければ検索ダイアログの修正は戻す
//------------------------------------------------------------------
//#define UZ_FIX_FINDBOX

//------------------------------------------------------------------
// アウトライン解析
//  - 正規表現を使用した場合はマッチした文字列のみリストに登録 2017.6.8
//------------------------------------------------------------------
#define UZ_FIX_OUTLINE

//-------------------------------------------------------------------------
// その他
//-------------------------------------------------------------------------

//------------------------------------------------------------------
// ウェイトカーソル 2015.7.9
//  - 一部、正しい位置に修正
//  - 文字列削除時に表示しない（アンドゥのときなど）
//------------------------------------------------------------------
#define UZ_FIX_WAITCUESOR

//------------------------------------------------------------------
// 検索ダイアログの「正規表現」が影響を受けないようにする
//  - 検索マーク切り替え時 2015.6.1
//  - インクリメンタルサーチ時 2016.12.14
//------------------------------------------------------------------
#define UZ_FIX_SEARCH_KEEP_REGEXP

//------------------------------------------------------------------
// 行番号が非表示でブックマークが表示のときブックマークは線で描画する 2017.1.13
//------------------------------------------------------------------
#define UZ_FIX_DRAW_BOOKMARK_LINE_NOGYOU

//------------------------------------------------------------------
// 行番号縦線を行番号の色で描画する 2016.12.21
//------------------------------------------------------------------
#define UZ_FIX_LINE_TERM_TYPE

//------------------------------------------------------------------
// 行番号背景が行番号縦線をはみ出しているのを修正 2017.6.20 
//------------------------------------------------------------------
#define UZ_FIX_LINE_BG_OVERFLOW

//------------------------------------------------------------------
// 偶数行背景はEOF以降は適用しない 2017.6.20 
//------------------------------------------------------------------
#define UZ_FIX_NOT_EVEN_LINE_FROM_EOF

//------------------------------------------------------------------
// ノート線はEOF以降は適用しない 2017.6.20 
//------------------------------------------------------------------
#define UZ_FIX_NOT_NOTE_LINE_FROM_EOF

//------------------------------------------------------------------
// カーソル移動時のちらつきを暫定で対処 2015.8.4
// カーソル上下移動時に次の条件?のときに画面の更新が間に合わずに描画が崩れる 2015.8.4
//  - キーリピートが早い
//  - 裏で描画を頻繁に行うアプリが動いている
//    →UpdateWindow() を呼び出すことで一時対応
//  - スクロールした時に ScrollWindowEx() と再描画の同期がとれていない?
//  - MacTypeなどを使用すると描画の負荷が高くなり顕著になる。使わない場合は高速にやると再現する
//    →MoveCursor()に処理をまとめてしばらく様子見 2015.8.5
//    →修正を無効化して様子見 2017.4.8
//      →水平スクロール時にちらつくので最有効化 2017.4.9
//------------------------------------------------------------------
#define UZ_FIX_FLICKER


//
//#define USE_SSE2

#endif /* MY_CONFIG_H */
