#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mylogfont ;
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_13__ {int selected; int NtfUnicode; scalar_t__ hwndCombo; scalar_t__ hwndEdit; void* font; void* defaultFont; scalar_t__ hwndNotify; int /*<<< orphan*/  unicode; scalar_t__ hwndSelf; } ;
struct TYPE_12__ {int style; int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; int /*<<< orphan*/  x; int /*<<< orphan*/  y; scalar_t__ hwndParent; } ;
struct TYPE_11__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
typedef  TYPE_1__ RECT ;
typedef  int LRESULT ;
typedef  int /*<<< orphan*/  LOGFONTW ;
typedef  scalar_t__ INT ;
typedef  scalar_t__ HWND ;
typedef  int /*<<< orphan*/  HMENU ;
typedef  int /*<<< orphan*/  HINSTANCE ;
typedef  void* HFONT ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  TYPE_2__ CREATESTRUCTA ;
typedef  TYPE_3__ COMBOEX_INFO ;

/* Variables and functions */
 TYPE_3__* Alloc (int) ; 
 int CBS_DROPDOWN ; 
 int CBS_DROPDOWNLIST ; 
 int CBS_NOINTEGRALHEIGHT ; 
 int CBS_OWNERDRAWFIXED ; 
 int /*<<< orphan*/  COMBOEX_AdjustEditPos (TYPE_3__*) ; 
 int /*<<< orphan*/  COMBOEX_ComboWndProc ; 
 int /*<<< orphan*/  COMBOEX_EditWndProc ; 
 int /*<<< orphan*/  COMBOEX_ReSize (TYPE_3__*) ; 
 int /*<<< orphan*/  COMBO_SUBCLASSID ; 
 void* CreateFontIndirectW (int /*<<< orphan*/ *) ; 
 scalar_t__ CreateWindowExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateWindowW (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_USEFONTINFO ; 
 int /*<<< orphan*/  EDIT_SUBCLASSID ; 
 int /*<<< orphan*/  EM_SETMARGINS ; 
 int ES_AUTOHSCROLL ; 
 int /*<<< orphan*/  GWLP_HINSTANCE ; 
 int /*<<< orphan*/  GWLP_ID ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  GetClientRect (scalar_t__,TYPE_1__*) ; 
 scalar_t__ GetWindowLongPtrW (scalar_t__,int /*<<< orphan*/ ) ; 
 int GetWindowLongW (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowRect (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  HWND_TOP ; 
 int /*<<< orphan*/  IsWindowUnicode (scalar_t__) ; 
 scalar_t__ NFR_ANSI ; 
 scalar_t__ NFR_UNICODE ; 
 int /*<<< orphan*/  NF_QUERY ; 
 int /*<<< orphan*/  SPI_GETICONTITLELOGFONT ; 
 int SWP_NOACTIVATE ; 
 int SWP_NOMOVE ; 
 int SWP_NOREDRAW ; 
 int SWP_NOZORDER ; 
 scalar_t__ SendMessageW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowLongPtrW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowPos (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  SetWindowSubclass (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SystemParametersInfoW (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ TRACE_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,scalar_t__) ; 
 int /*<<< orphan*/  WC_COMBOBOXW ; 
 int /*<<< orphan*/  WC_EDITW ; 
 int /*<<< orphan*/  WM_GETFONT ; 
 int /*<<< orphan*/  WM_NOTIFYFORMAT ; 
 int /*<<< orphan*/  WM_SETFONT ; 
 int WS_CHILD ; 
 int WS_CLIPCHILDREN ; 
 int WS_CLIPSIBLINGS ; 
 int WS_VISIBLE ; 
 int WS_VSCROLL ; 
 int /*<<< orphan*/  comboex ; 
 int /*<<< orphan*/  wine_dbgstr_rect (TYPE_1__*) ; 

__attribute__((used)) static LRESULT COMBOEX_Create (HWND hwnd, CREATESTRUCTA const *cs)
{
    static const WCHAR NIL[] = { 0 };
    COMBOEX_INFO *infoPtr;
    LOGFONTW mylogfont;
    RECT win_rect;
    INT i;

    /* allocate memory for info structure */
    infoPtr = Alloc (sizeof(COMBOEX_INFO));
    if (!infoPtr) return -1;

    /* initialize info structure */
    /* note that infoPtr is allocated zero-filled */

    infoPtr->hwndSelf = hwnd;
    infoPtr->selected = -1;

    infoPtr->unicode = IsWindowUnicode (hwnd);
    infoPtr->hwndNotify = cs->hwndParent;

    i = SendMessageW(infoPtr->hwndNotify, WM_NOTIFYFORMAT, (WPARAM)hwnd, NF_QUERY);
    if ((i != NFR_ANSI) && (i != NFR_UNICODE)) {
	WARN("wrong response to WM_NOTIFYFORMAT (%d), assuming ANSI\n", i);
	i = NFR_ANSI;
    }
    infoPtr->NtfUnicode = (i == NFR_UNICODE);

    SetWindowLongPtrW (hwnd, 0, (DWORD_PTR)infoPtr);

    if (TRACE_ON(comboex)) {
	RECT client, rect;
	GetWindowRect(hwnd, &rect);
	GetClientRect(hwnd, &client);
	TRACE("EX window=(%s), client=(%s)\n",
		wine_dbgstr_rect(&rect), wine_dbgstr_rect(&client));
    }

    /* Native version of ComboEx creates the ComboBox with DROPDOWNLIST */
    /* specified. It then creates its own version of the EDIT control   */
    /* and makes the ComboBox the parent. This is because a normal      */
    /* DROPDOWNLIST does not have an EDIT control, but we need one.     */
    /* We also need to place the edit control at the proper location    */
    /* (allow space for the icons).                                     */

    infoPtr->hwndCombo = CreateWindowW (WC_COMBOBOXW, NIL,
                         WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VSCROLL |
                         CBS_NOINTEGRALHEIGHT | CBS_DROPDOWNLIST |
			 WS_CHILD | WS_VISIBLE | CBS_OWNERDRAWFIXED |
			 GetWindowLongW (hwnd, GWL_STYLE),
			 cs->y, cs->x, cs->cx, cs->cy, hwnd,
			 (HMENU) GetWindowLongPtrW (hwnd, GWLP_ID),
			 (HINSTANCE)GetWindowLongPtrW (hwnd, GWLP_HINSTANCE), NULL);

    SetWindowSubclass(infoPtr->hwndCombo, COMBOEX_ComboWndProc, COMBO_SUBCLASSID,
                      (DWORD_PTR)hwnd);
    infoPtr->font = (HFONT)SendMessageW (infoPtr->hwndCombo, WM_GETFONT, 0, 0);

    /*
     * Now create our own EDIT control so we can position it.
     * It is created only for CBS_DROPDOWN style
     */
    if ((cs->style & CBS_DROPDOWNLIST) == CBS_DROPDOWN) {
	infoPtr->hwndEdit = CreateWindowExW (0, WC_EDITW, NIL,
		    WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | ES_AUTOHSCROLL,
		    0, 0, 0, 0,  /* will set later */
		    infoPtr->hwndCombo,
		    (HMENU) GetWindowLongPtrW (hwnd, GWLP_ID),
		    (HINSTANCE)GetWindowLongPtrW (hwnd, GWLP_HINSTANCE), NULL);

	SetWindowSubclass(infoPtr->hwndEdit, COMBOEX_EditWndProc, EDIT_SUBCLASSID,
	                  (DWORD_PTR)hwnd);

	infoPtr->font = (HFONT)SendMessageW(infoPtr->hwndCombo, WM_GETFONT, 0, 0);
    }

    /*
     * Locate the default font if necessary and then set it in
     * all associated controls
     */
    if (!infoPtr->font) {
	SystemParametersInfoW (SPI_GETICONTITLELOGFONT, sizeof(mylogfont),
			       &mylogfont, 0);
	infoPtr->font = infoPtr->defaultFont = CreateFontIndirectW (&mylogfont);
    }
    SendMessageW (infoPtr->hwndCombo, WM_SETFONT, (WPARAM)infoPtr->font, 0);
    if (infoPtr->hwndEdit) {
	SendMessageW (infoPtr->hwndEdit, WM_SETFONT, (WPARAM)infoPtr->font, 0);
       SendMessageW (infoPtr->hwndEdit, EM_SETMARGINS, EC_USEFONTINFO, 0);
    }

    COMBOEX_ReSize (infoPtr);

    /* Above is fairly certain, below is much less certain. */

    GetWindowRect(hwnd, &win_rect);

    if (TRACE_ON(comboex)) {
	RECT client, rect;
	GetClientRect(hwnd, &client);
	GetWindowRect(infoPtr->hwndCombo, &rect);
	TRACE("EX window=(%s) client=(%s) CB wnd=(%s)\n",
		wine_dbgstr_rect(&win_rect), wine_dbgstr_rect(&client),
		wine_dbgstr_rect(&rect));
    }
    SetWindowPos(infoPtr->hwndCombo, HWND_TOP, 0, 0,
		 win_rect.right - win_rect.left, win_rect.bottom - win_rect.top,
		 SWP_NOACTIVATE | SWP_NOREDRAW);

    GetWindowRect(infoPtr->hwndCombo, &win_rect);
    TRACE("CB window=(%s)\n", wine_dbgstr_rect(&win_rect));
    SetWindowPos(hwnd, HWND_TOP, 0, 0,
		 win_rect.right - win_rect.left, win_rect.bottom - win_rect.top,
		 SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOMOVE);

    COMBOEX_AdjustEditPos (infoPtr);

    return 0;
}