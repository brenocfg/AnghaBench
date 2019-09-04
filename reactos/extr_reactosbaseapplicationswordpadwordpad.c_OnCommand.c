#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pf ;
typedef  int /*<<< orphan*/  fmt ;
typedef  int /*<<< orphan*/  cf ;
typedef  int WPARAM ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_22__ {int member_1; int cpMax; int cpMin; int /*<<< orphan*/  member_0; } ;
struct TYPE_21__ {int cbSize; int /*<<< orphan*/  dwItemData; int /*<<< orphan*/  fMask; } ;
struct TYPE_20__ {int cbSize; int dxOffset; int /*<<< orphan*/  wNumbering; int /*<<< orphan*/  dwMask; } ;
struct TYPE_19__ {int cbSize; int dwEffects; int /*<<< orphan*/  wAlignment; int /*<<< orphan*/  dwMask; int /*<<< orphan*/  crTextColor; } ;
struct TYPE_18__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_17__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  left; } ;
struct TYPE_16__ {int codepage; int /*<<< orphan*/  flags; } ;
struct TYPE_14__ {int cpMax; int /*<<< orphan*/  cpMin; } ;
struct TYPE_15__ {int /*<<< orphan*/ * lpstrText; TYPE_1__ chrg; } ;
typedef  TYPE_2__ TEXTRANGEW ;
typedef  TYPE_3__ SETTEXTEX ;
typedef  TYPE_4__ RECT ;
typedef  TYPE_5__ POINT ;
typedef  TYPE_6__ PARAFORMAT2 ;
typedef  TYPE_7__ PARAFORMAT ;
typedef  TYPE_8__ MENUITEMINFOW ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  scalar_t__ LPARAM ;
typedef  int LONG ;
typedef  scalar_t__ HWND ;
typedef  int /*<<< orphan*/  HMENU ;
typedef  int /*<<< orphan*/  HINSTANCE ;
typedef  int /*<<< orphan*/  FINDREPLACEW ;
typedef  int DWORD ;
typedef  TYPE_9__ CHARRANGE ;
typedef  TYPE_6__ CHARFORMAT2W ;

/* Variables and functions */
 int BANDID_FONTLIST ; 
 int BANDID_FORMATBAR ; 
 int BANDID_RULER ; 
 int BANDID_SIZELIST ; 
 int BANDID_STATUSBAR ; 
 int BANDID_TOOLBAR ; 
 int /*<<< orphan*/  CBN_SELENDOK ; 
 int CFE_AUTOCOLOR ; 
 int CFE_BOLD ; 
 int CFE_ITALIC ; 
 int CFE_UNDERLINE ; 
 int /*<<< orphan*/  CFM_BOLD ; 
 int /*<<< orphan*/  CFM_COLOR ; 
 int /*<<< orphan*/  CFM_ITALIC ; 
 int /*<<< orphan*/  CFM_UNDERLINE ; 
 int /*<<< orphan*/  ClientToScreen (scalar_t__,TYPE_5__*) ; 
 int DialogBoxW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DialogOpenFile () ; 
 int /*<<< orphan*/  DialogSaveFile () ; 
 int /*<<< orphan*/  DoOpenFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DoSaveFile (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EM_EXGETSEL ; 
 int /*<<< orphan*/  EM_EXSETSEL ; 
 int /*<<< orphan*/  EM_GETCHARFORMAT ; 
 int /*<<< orphan*/  EM_GETMODIFY ; 
 int /*<<< orphan*/  EM_GETPARAFORMAT ; 
 int /*<<< orphan*/  EM_GETSELTEXT ; 
 int /*<<< orphan*/  EM_GETTEXTRANGE ; 
 int /*<<< orphan*/  EM_REDO ; 
 int /*<<< orphan*/  EM_SETBKGNDCOLOR ; 
 int /*<<< orphan*/  EM_SETCHARFORMAT ; 
 int /*<<< orphan*/  EM_SETMODIFY ; 
 int /*<<< orphan*/  EM_SETPARAFORMAT ; 
 int /*<<< orphan*/  EM_SETREADONLY ; 
 int /*<<< orphan*/  EM_SETTEXTEX ; 
 int /*<<< orphan*/  EM_UNDO ; 
 int ES_READONLY ; 
 int FALSE ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 scalar_t__ GetDlgItem (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetMenu (scalar_t__) ; 
 int /*<<< orphan*/  GetMenuItemInfoW (int /*<<< orphan*/ ,int,int,TYPE_8__*) ; 
 int /*<<< orphan*/  GetModuleHandleW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  GetSubMenu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GetWindowLongW (scalar_t__,int /*<<< orphan*/ ) ; 
 int GetWindowTextLengthW (scalar_t__) ; 
 int /*<<< orphan*/  GetWindowTextW (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  HIWORD (int) ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDC_EDITOR ; 
#define  IDC_FONTLIST 179 
 int /*<<< orphan*/  IDC_FORMATBAR ; 
 int /*<<< orphan*/  IDC_REBAR ; 
#define  IDC_SIZELIST 178 
 int /*<<< orphan*/  IDD_DATETIME ; 
 int /*<<< orphan*/  IDD_NEWFILE ; 
 int /*<<< orphan*/  IDD_PARAFORMAT ; 
 int /*<<< orphan*/  IDD_TABSTOPS ; 
#define  ID_ABOUT 177 
#define  ID_ALIGN_CENTER 176 
#define  ID_ALIGN_LEFT 175 
#define  ID_ALIGN_RIGHT 174 
#define  ID_BACK_1 173 
#define  ID_BACK_2 172 
#define  ID_BULLET 171 
 int ID_COLOR_AUTOMATIC ; 
 int ID_COLOR_FIRST ; 
#define  ID_DATETIME 170 
#define  ID_EDIT_CHARFORMAT 169 
#define  ID_EDIT_CLEAR 168 
#define  ID_EDIT_COPY 167 
#define  ID_EDIT_CUT 166 
#define  ID_EDIT_DEFCHARFORMAT 165 
#define  ID_EDIT_GETTEXT 164 
#define  ID_EDIT_MODIFIED 163 
#define  ID_EDIT_PARAFORMAT 162 
#define  ID_EDIT_PASTE 161 
#define  ID_EDIT_READONLY 160 
#define  ID_EDIT_REDO 159 
#define  ID_EDIT_SELECTALL 158 
#define  ID_EDIT_SELECTIONINFO 157 
#define  ID_EDIT_UNDO 156 
#define  ID_FILE_EXIT 155 
#define  ID_FILE_NEW 154 
#define  ID_FILE_OPEN 153 
#define  ID_FILE_RECENT1 152 
#define  ID_FILE_RECENT2 151 
#define  ID_FILE_RECENT3 150 
#define  ID_FILE_RECENT4 149 
#define  ID_FILE_SAVE 148 
#define  ID_FILE_SAVEAS 147 
#define  ID_FIND 146 
#define  ID_FIND_NEXT 145 
#define  ID_FONTSETTINGS 144 
#define  ID_FORMAT_BOLD 143 
#define  ID_FORMAT_COLOR 142 
#define  ID_FORMAT_ITALIC 141 
#define  ID_FORMAT_UNDERLINE 140 
 int ID_NEWFILE_ABORT ; 
#define  ID_PARAFORMAT 139 
#define  ID_PREVIEW 138 
#define  ID_PRINT 137 
#define  ID_PRINTSETUP 136 
#define  ID_PRINT_QUICK 135 
#define  ID_REPLACE 134 
#define  ID_TABSTOPS 133 
#define  ID_TOGGLE_FORMATBAR 132 
#define  ID_TOGGLE_RULER 131 
#define  ID_TOGGLE_STATUSBAR 130 
#define  ID_TOGGLE_TOOLBAR 129 
#define  ID_VIEWPROPERTIES 128 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int LF_FACESIZE ; 
 int LOWORD (int) ; 
 int /*<<< orphan*/  MAKEINTRESOURCEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_STRING_LEN ; 
 int /*<<< orphan*/  MB_OK ; 
 int /*<<< orphan*/  MIIM_DATA ; 
 int /*<<< orphan*/  MessageBoxA (scalar_t__,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MessageBoxW (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PFA_CENTER ; 
 int /*<<< orphan*/  PFA_LEFT ; 
 int /*<<< orphan*/  PFA_RIGHT ; 
 int /*<<< orphan*/  PFM_ALIGNMENT ; 
 int /*<<< orphan*/  PFM_NUMBERING ; 
 int /*<<< orphan*/  PFM_OFFSET ; 
 int /*<<< orphan*/  PFN_BULLET ; 
 int /*<<< orphan*/  PostMessageW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RGB (int,int,int) ; 
 int SCF_SELECTION ; 
 int /*<<< orphan*/  ST_DEFAULT ; 
 int SendMessageW (scalar_t__,int /*<<< orphan*/ ,int const,scalar_t__) ; 
 int /*<<< orphan*/  SetMenu (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ShowWindow (scalar_t__,int) ; 
 int /*<<< orphan*/  TB_COMMANDTOINDEX ; 
 int /*<<< orphan*/  TB_GETITEMRECT ; 
 int TPM_LEFTALIGN ; 
 int TPM_LEFTBUTTON ; 
 int TPM_NONOTIFY ; 
 int TPM_RETURNCMD ; 
 int TPM_TOPALIGN ; 
 int TRUE ; 
 int TrackPopupMenu (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_CLEAR ; 
 int /*<<< orphan*/  WM_CLOSE ; 
 int /*<<< orphan*/  WM_COMMAND ; 
 int /*<<< orphan*/  WM_COPY ; 
 int /*<<< orphan*/  WM_CUT ; 
 int /*<<< orphan*/  WM_PASTE ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_6__*,int) ; 
 int* barState ; 
 int /*<<< orphan*/  clear_formatting () ; 
 int /*<<< orphan*/  datetime_proc ; 
 int /*<<< orphan*/  dialog_about () ; 
 int /*<<< orphan*/  dialog_choose_font () ; 
 int /*<<< orphan*/  dialog_find (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dialog_print (scalar_t__,char*) ; 
 int /*<<< orphan*/  dialog_printsetup (scalar_t__) ; 
 int /*<<< orphan*/  dialog_viewproperties () ; 
 int /*<<< orphan*/  fileFormat ; 
 int /*<<< orphan*/  get_comboexlist_selection (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hColorPopupMenu ; 
 scalar_t__ hEditorWnd ; 
 int /*<<< orphan*/  hMainWnd ; 
 int /*<<< orphan*/  handle_findmsg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_preview (scalar_t__,char*) ; 
 int /*<<< orphan*/  is_bar_visible (int) ; 
 int /*<<< orphan*/  newfile_proc ; 
 int /*<<< orphan*/  on_fontlist_modified (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_sizelist_modified (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  paraformat_proc ; 
 int /*<<< orphan*/  print_quick (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  prompt_save_changes () ; 
 size_t reg_formatindex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bar_states () ; 
 int /*<<< orphan*/  set_caption (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_fileformat (int) ; 
 int /*<<< orphan*/  set_statusbar_state (int) ; 
 int /*<<< orphan*/  set_toolbar_state (int,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 
 int /*<<< orphan*/  tabstops_proc ; 
 int /*<<< orphan*/  target_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * textcolors ; 
 int /*<<< orphan*/  update_font_list () ; 
 int /*<<< orphan*/  update_window () ; 
 int /*<<< orphan*/ * wordWrap ; 
 int /*<<< orphan*/  wszAppTitle ; 
 char* wszFileName ; 

__attribute__((used)) static LRESULT OnCommand( HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    HWND hwndEditor = GetDlgItem(hWnd, IDC_EDITOR);
    static FINDREPLACEW findreplace;

    if ((HWND)lParam == hwndEditor)
        return 0;

    switch(LOWORD(wParam))
    {

    case ID_FILE_EXIT:
        PostMessageW(hWnd, WM_CLOSE, 0, 0);
        break;

    case ID_FILE_NEW:
        {
            HINSTANCE hInstance = GetModuleHandleW(0);
            int ret = DialogBoxW(hInstance, MAKEINTRESOURCEW(IDD_NEWFILE), hWnd, newfile_proc);

            if(ret != ID_NEWFILE_ABORT)
            {
                if(prompt_save_changes())
                {
                    SETTEXTEX st;

                    set_caption(NULL);
                    wszFileName[0] = '\0';

                    clear_formatting();

                    st.flags = ST_DEFAULT;
                    st.codepage = 1200;
                    SendMessageW(hEditorWnd, EM_SETTEXTEX, (WPARAM)&st, 0);

                    SendMessageW(hEditorWnd, EM_SETMODIFY, FALSE, 0);
                    set_fileformat(ret);
                    update_font_list();
                }
            }
        }
        break;

    case ID_FILE_OPEN:
        DialogOpenFile();
        break;

    case ID_FILE_SAVE:
        if(wszFileName[0])
        {
            DoSaveFile(wszFileName, fileFormat);
            break;
        }
        /* Fall through */

    case ID_FILE_SAVEAS:
        DialogSaveFile();
        break;

    case ID_FILE_RECENT1:
    case ID_FILE_RECENT2:
    case ID_FILE_RECENT3:
    case ID_FILE_RECENT4:
        {
            HMENU hMenu = GetMenu(hWnd);
            MENUITEMINFOW mi;

            mi.cbSize = sizeof(MENUITEMINFOW);
            mi.fMask = MIIM_DATA;
            if(GetMenuItemInfoW(hMenu, LOWORD(wParam), FALSE, &mi))
                DoOpenFile((LPWSTR)mi.dwItemData);
        }
        break;

    case ID_FIND:
        dialog_find(&findreplace, FALSE);
        break;

    case ID_FIND_NEXT:
        handle_findmsg(&findreplace);
        break;

    case ID_REPLACE:
        dialog_find(&findreplace, TRUE);
        break;

    case ID_FONTSETTINGS:
        dialog_choose_font();
        break;

    case ID_PRINT:
        dialog_print(hWnd, wszFileName);
        target_device(hMainWnd, wordWrap[reg_formatindex(fileFormat)]);
        break;

    case ID_PRINT_QUICK:
        print_quick(hMainWnd, wszFileName);
        target_device(hMainWnd, wordWrap[reg_formatindex(fileFormat)]);
        break;

    case ID_PREVIEW:
        {
            int index = reg_formatindex(fileFormat);
            DWORD tmp = barState[index];
            barState[index] = 1 << BANDID_STATUSBAR;
            set_bar_states();
            barState[index] = tmp;
            ShowWindow(hEditorWnd, FALSE);

            init_preview(hWnd, wszFileName);

            SetMenu(hWnd, NULL);
            InvalidateRect(0, 0, TRUE);
        }
        break;

    case ID_PRINTSETUP:
        dialog_printsetup(hWnd);
        target_device(hMainWnd, wordWrap[reg_formatindex(fileFormat)]);
        break;

    case ID_FORMAT_BOLD:
    case ID_FORMAT_ITALIC:
    case ID_FORMAT_UNDERLINE:
        {
        CHARFORMAT2W fmt;
        int effects = CFE_BOLD;

        ZeroMemory(&fmt, sizeof(fmt));
        fmt.cbSize = sizeof(fmt);
        SendMessageW(hwndEditor, EM_GETCHARFORMAT, SCF_SELECTION, (LPARAM)&fmt);

        fmt.dwMask = CFM_BOLD;

        if (LOWORD(wParam) == ID_FORMAT_ITALIC)
        {
            effects = CFE_ITALIC;
            fmt.dwMask = CFM_ITALIC;
        } else if (LOWORD(wParam) == ID_FORMAT_UNDERLINE)
        {
            effects = CFE_UNDERLINE;
            fmt.dwMask = CFM_UNDERLINE;
        }

        fmt.dwEffects ^= effects;

        SendMessageW(hwndEditor, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&fmt);
        break;
        }

    case ID_FORMAT_COLOR:
    {
        HWND hReBarWnd = GetDlgItem(hWnd, IDC_REBAR);
        HWND hFormatBarWnd = GetDlgItem(hReBarWnd, IDC_FORMATBAR);
        HMENU hPop;
        RECT itemrc;
        POINT pt;
        int mid;
        int itemidx = SendMessageW(hFormatBarWnd, TB_COMMANDTOINDEX, ID_FORMAT_COLOR, 0);

        SendMessageW(hFormatBarWnd, TB_GETITEMRECT, itemidx, (LPARAM)&itemrc);
        pt.x = itemrc.left;
        pt.y = itemrc.bottom;
        ClientToScreen(hFormatBarWnd, &pt);
        hPop = GetSubMenu(hColorPopupMenu, 0);
        mid = TrackPopupMenu(hPop, TPM_LEFTALIGN | TPM_TOPALIGN | TPM_LEFTBUTTON |
                                   TPM_RETURNCMD | TPM_NONOTIFY,
                             pt.x, pt.y, 0, hWnd, 0);
        if (mid >= ID_COLOR_FIRST && mid <= ID_COLOR_AUTOMATIC)
        {
            CHARFORMAT2W fmt;

            ZeroMemory(&fmt, sizeof(fmt));
            fmt.cbSize = sizeof(fmt);
            SendMessageW(hwndEditor, EM_GETCHARFORMAT, SCF_SELECTION, (LPARAM)&fmt);

            fmt.dwMask = CFM_COLOR;

            if (mid < ID_COLOR_AUTOMATIC) {
                fmt.crTextColor = textcolors[mid - ID_COLOR_FIRST];
                fmt.dwEffects &= ~CFE_AUTOCOLOR;
            } else {
                fmt.dwEffects |= CFE_AUTOCOLOR;
            }

            SendMessageW(hwndEditor, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&fmt);
        }
        break;
    }

    case ID_EDIT_CUT:
        PostMessageW(hwndEditor, WM_CUT, 0, 0);
        break;

    case ID_EDIT_COPY:
        PostMessageW(hwndEditor, WM_COPY, 0, 0);
        break;

    case ID_EDIT_PASTE:
        PostMessageW(hwndEditor, WM_PASTE, 0, 0);
        break;

    case ID_EDIT_CLEAR:
        PostMessageW(hwndEditor, WM_CLEAR, 0, 0);
        break;

    case ID_EDIT_SELECTALL:
        {
        CHARRANGE range = {0, -1};
        SendMessageW(hwndEditor, EM_EXSETSEL, 0, (LPARAM)&range);
        /* SendMessage(hwndEditor, EM_SETSEL, 0, -1); */
        return 0;
        }

    case ID_EDIT_GETTEXT:
        {
        int nLen = GetWindowTextLengthW(hwndEditor);
        LPWSTR data = HeapAlloc( GetProcessHeap(), 0, (nLen+1)*sizeof(WCHAR) );
        TEXTRANGEW tr;

        GetWindowTextW(hwndEditor, data, nLen+1);
        MessageBoxW(NULL, data, wszAppTitle, MB_OK);

        HeapFree( GetProcessHeap(), 0, data);
        data = HeapAlloc(GetProcessHeap(), 0, (nLen+1)*sizeof(WCHAR));
        tr.chrg.cpMin = 0;
        tr.chrg.cpMax = nLen;
        tr.lpstrText = data;
        SendMessageW(hwndEditor, EM_GETTEXTRANGE, 0, (LPARAM)&tr);
        MessageBoxW(NULL, data, wszAppTitle, MB_OK);
        HeapFree( GetProcessHeap(), 0, data );

        /* SendMessage(hwndEditor, EM_SETSEL, 0, -1); */
        return 0;
        }

    case ID_EDIT_CHARFORMAT:
    case ID_EDIT_DEFCHARFORMAT:
        {
        CHARFORMAT2W cf;

        ZeroMemory(&cf, sizeof(cf));
        cf.cbSize = sizeof(cf);
        cf.dwMask = 0;
        SendMessageW(hwndEditor, EM_GETCHARFORMAT,
                     LOWORD(wParam) == ID_EDIT_CHARFORMAT, (LPARAM)&cf);
        return 0;
        }

    case ID_EDIT_PARAFORMAT:
        {
        PARAFORMAT2 pf;
        ZeroMemory(&pf, sizeof(pf));
        pf.cbSize = sizeof(pf);
        SendMessageW(hwndEditor, EM_GETPARAFORMAT, 0, (LPARAM)&pf);
        return 0;
        }

    case ID_EDIT_SELECTIONINFO:
        {
        CHARRANGE range = {0, -1};
        char buf[128];
        WCHAR *data = NULL;

        SendMessageW(hwndEditor, EM_EXGETSEL, 0, (LPARAM)&range);
        data = HeapAlloc(GetProcessHeap(), 0, sizeof(*data) * (range.cpMax-range.cpMin+1));
        SendMessageW(hwndEditor, EM_GETSELTEXT, 0, (LPARAM)data);
        sprintf(buf, "Start = %d, End = %d", range.cpMin, range.cpMax);
        MessageBoxA(hWnd, buf, "Editor", MB_OK);
        MessageBoxW(hWnd, data, wszAppTitle, MB_OK);
        HeapFree( GetProcessHeap(), 0, data);
        /* SendMessage(hwndEditor, EM_SETSEL, 0, -1); */
        return 0;
        }

    case ID_EDIT_READONLY:
        {
        LONG nStyle = GetWindowLongW(hwndEditor, GWL_STYLE);
        if (nStyle & ES_READONLY)
            SendMessageW(hwndEditor, EM_SETREADONLY, 0, 0);
        else
            SendMessageW(hwndEditor, EM_SETREADONLY, 1, 0);
        return 0;
        }

    case ID_EDIT_MODIFIED:
        if (SendMessageW(hwndEditor, EM_GETMODIFY, 0, 0))
            SendMessageW(hwndEditor, EM_SETMODIFY, 0, 0);
        else
            SendMessageW(hwndEditor, EM_SETMODIFY, 1, 0);
        return 0;

    case ID_EDIT_UNDO:
        SendMessageW(hwndEditor, EM_UNDO, 0, 0);
        return 0;

    case ID_EDIT_REDO:
        SendMessageW(hwndEditor, EM_REDO, 0, 0);
        return 0;

    case ID_BULLET:
        {
            PARAFORMAT pf;

            pf.cbSize = sizeof(pf);
            pf.dwMask = PFM_NUMBERING;
            SendMessageW(hwndEditor, EM_GETPARAFORMAT, 0, (LPARAM)&pf);

            pf.dwMask |=  PFM_OFFSET;

            if(pf.wNumbering == PFN_BULLET)
            {
                pf.wNumbering = 0;
                pf.dxOffset = 0;
            } else
            {
                pf.wNumbering = PFN_BULLET;
                pf.dxOffset = 720;
            }

            SendMessageW(hwndEditor, EM_SETPARAFORMAT, 0, (LPARAM)&pf);
        }
        break;

    case ID_ALIGN_LEFT:
    case ID_ALIGN_CENTER:
    case ID_ALIGN_RIGHT:
        {
        PARAFORMAT2 pf;

        pf.cbSize = sizeof(pf);
        pf.dwMask = PFM_ALIGNMENT;
        switch(LOWORD(wParam)) {
        case ID_ALIGN_LEFT: pf.wAlignment = PFA_LEFT; break;
        case ID_ALIGN_CENTER: pf.wAlignment = PFA_CENTER; break;
        case ID_ALIGN_RIGHT: pf.wAlignment = PFA_RIGHT; break;
        }
        SendMessageW(hwndEditor, EM_SETPARAFORMAT, 0, (LPARAM)&pf);
        break;
        }

    case ID_BACK_1:
        SendMessageW(hwndEditor, EM_SETBKGNDCOLOR, 1, 0);
        break;

    case ID_BACK_2:
        SendMessageW(hwndEditor, EM_SETBKGNDCOLOR, 0, RGB(255,255,192));
        break;

    case ID_TOGGLE_TOOLBAR:
        set_toolbar_state(BANDID_TOOLBAR, !is_bar_visible(BANDID_TOOLBAR));
        update_window();
        break;

    case ID_TOGGLE_FORMATBAR:
        set_toolbar_state(BANDID_FONTLIST, !is_bar_visible(BANDID_FORMATBAR));
        set_toolbar_state(BANDID_SIZELIST, !is_bar_visible(BANDID_FORMATBAR));
        set_toolbar_state(BANDID_FORMATBAR, !is_bar_visible(BANDID_FORMATBAR));
        update_window();
        break;

    case ID_TOGGLE_STATUSBAR:
        set_statusbar_state(!is_bar_visible(BANDID_STATUSBAR));
        update_window();
        break;

    case ID_TOGGLE_RULER:
        set_toolbar_state(BANDID_RULER, !is_bar_visible(BANDID_RULER));
        update_window();
        break;

    case ID_DATETIME:
        DialogBoxW(GetModuleHandleW(0), MAKEINTRESOURCEW(IDD_DATETIME), hWnd, datetime_proc);
        break;

    case ID_PARAFORMAT:
        DialogBoxW(GetModuleHandleW(0), MAKEINTRESOURCEW(IDD_PARAFORMAT), hWnd, paraformat_proc);
        break;

    case ID_TABSTOPS:
        DialogBoxW(GetModuleHandleW(0), MAKEINTRESOURCEW(IDD_TABSTOPS), hWnd, tabstops_proc);
        break;

    case ID_ABOUT:
        dialog_about();
        break;

    case ID_VIEWPROPERTIES:
        dialog_viewproperties();
        break;

    case IDC_FONTLIST:
        if (HIWORD(wParam) == CBN_SELENDOK)
        {
            WCHAR buffer[LF_FACESIZE];
            HWND hwndFontList = (HWND)lParam;
            get_comboexlist_selection(hwndFontList, buffer, LF_FACESIZE);
            on_fontlist_modified(buffer);
        }
        break;

    case IDC_SIZELIST:
        if (HIWORD(wParam) == CBN_SELENDOK)
        {
            WCHAR buffer[MAX_STRING_LEN+1];
            HWND hwndSizeList = (HWND)lParam;
            get_comboexlist_selection(hwndSizeList, buffer, MAX_STRING_LEN+1);
            on_sizelist_modified(hwndSizeList, buffer);
        }
        break;

    default:
        SendMessageW(hwndEditor, WM_COMMAND, wParam, lParam);
        break;
    }
    return 0;
}