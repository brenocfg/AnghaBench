#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  int UINT ;
struct TYPE_12__ {scalar_t__ bottom; scalar_t__ left; scalar_t__ top; scalar_t__ right; } ;
struct TYPE_11__ {scalar_t__ top; scalar_t__ left; scalar_t__ bottom; scalar_t__ right; } ;
struct TYPE_10__ {int dwStyle; int wState; int visibleItems; void* hWndLBox; void* hWndEdit; TYPE_8__ textRect; TYPE_2__ droppedRect; int /*<<< orphan*/  buttonRect; scalar_t__ owner; scalar_t__ editHeight; scalar_t__ droppedWidth; } ;
typedef  int LRESULT ;
typedef  int /*<<< orphan*/  LPPOINT ;
typedef  TYPE_1__* LPHEADCOMBO ;
typedef  int LONG ;
typedef  scalar_t__ HWND ;
typedef  int /*<<< orphan*/  HMENU ;
typedef  int /*<<< orphan*/  HINSTANCE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CBCalcPlacement (scalar_t__,TYPE_1__*,TYPE_8__*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int CBF_EDIT ; 
 int CBF_MEASUREITEM ; 
 int /*<<< orphan*/  CBForceDummyResize (TYPE_1__*) ; 
 int CBS_AUTOHSCROLL ; 
 int CBS_DISABLENOSCROLL ; 
 int CBS_DROPDOWN ; 
 int CBS_DROPDOWNLIST ; 
 int CBS_HASSTRINGS ; 
 int CBS_LOWERCASE ; 
 int CBS_NOINTEGRALHEIGHT ; 
 int CBS_OEMCONVERT ; 
 int CBS_OWNERDRAWFIXED ; 
 int CBS_OWNERDRAWVARIABLE ; 
 int CBS_SIMPLE ; 
 int CBS_SORT ; 
 int CBS_UPPERCASE ; 
 int CB_GETTYPE (TYPE_1__*) ; 
 scalar_t__ COMBO_EDITBUTTONSPACE () ; 
 scalar_t__ COMBO_YBORDERSIZE () ; 
 void* CreateWindowExW (int,char const*,int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int ES_AUTOHSCROLL ; 
 int ES_COMBO ; 
 int ES_LEFT ; 
 int ES_LOWERCASE ; 
 int ES_NOHIDESEL ; 
 int ES_OEMCONVERT ; 
 int ES_UPPERCASE ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GWLP_HINSTANCE ; 
 int /*<<< orphan*/  GetClientRect (scalar_t__,TYPE_2__*) ; 
 scalar_t__ GetWindowLongPtrW (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HWND_DESKTOP ; 
 scalar_t__ ID_CB_EDIT ; 
 scalar_t__ ID_CB_LISTBOX ; 
 int /*<<< orphan*/  IsWindowEnabled (scalar_t__) ; 
 int LBS_COMBOBOX ; 
 int LBS_DISABLENOSCROLL ; 
 int LBS_HASSTRINGS ; 
 int LBS_NOINTEGRALHEIGHT ; 
 int LBS_NOTIFY ; 
 int LBS_SORT ; 
 int /*<<< orphan*/  MapWindowPoints (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OpenThemeData (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetParent (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WC_COMBOBOXW ; 
 int WS_BORDER ; 
 int WS_CHILD ; 
 int WS_CLIPSIBLINGS ; 
 int WS_DISABLED ; 
 int WS_EX_CLIENTEDGE ; 
 int WS_EX_TOOLWINDOW ; 
 int WS_EX_TOPMOST ; 
 int WS_VISIBLE ; 
 int WS_VSCROLL ; 

__attribute__((used)) static LRESULT COMBO_Create( HWND hwnd, LPHEADCOMBO lphc, HWND hwndParent, LONG style )
{
  static const WCHAR clbName[] = {'C','o','m','b','o','L','B','o','x',0};
  static const WCHAR editName[] = {'E','d','i','t',0};

  OpenThemeData( hwnd, WC_COMBOBOXW );
  if( !CB_GETTYPE(lphc) ) lphc->dwStyle |= CBS_SIMPLE;
  if( CB_GETTYPE(lphc) != CBS_DROPDOWNLIST ) lphc->wState |= CBF_EDIT;

  lphc->owner = hwndParent;

  /*
   * The item height and dropped width are not set when the control
   * is created.
   */
  lphc->droppedWidth = lphc->editHeight = 0;

  /*
   * The first time we go through, we want to measure the ownerdraw item
   */
  lphc->wState |= CBF_MEASUREITEM;

  /*
   * Per default the comctl32 version of combo shows up to 30 items
   */
  lphc->visibleItems = 30;

  /* M$ IE 3.01 actually creates (and rapidly destroys) an ownerless combobox */

  if( lphc->owner || !(style & WS_VISIBLE) )
  {
      UINT lbeStyle   = 0;
      UINT lbeExStyle = 0;

      /*
       * Initialize the dropped rect to the size of the client area of the
       * control and then, force all the areas of the combobox to be
       * recalculated.
       */
      GetClientRect( hwnd, &lphc->droppedRect );
      CBCalcPlacement(hwnd, lphc, &lphc->textRect, &lphc->buttonRect, &lphc->droppedRect );

      /*
       * Adjust the position of the popup listbox if it's necessary
       */
      if ( CB_GETTYPE(lphc) != CBS_SIMPLE )
      {
	lphc->droppedRect.top   = lphc->textRect.bottom + COMBO_YBORDERSIZE();

	/*
	 * If it's a dropdown, the listbox is offset
	 */
	if( CB_GETTYPE(lphc) == CBS_DROPDOWN )
	  lphc->droppedRect.left += COMBO_EDITBUTTONSPACE();

        if (lphc->droppedRect.bottom < lphc->droppedRect.top)
            lphc->droppedRect.bottom = lphc->droppedRect.top;
        if (lphc->droppedRect.right < lphc->droppedRect.left)
            lphc->droppedRect.right = lphc->droppedRect.left;
        MapWindowPoints( hwnd, 0, (LPPOINT)&lphc->droppedRect, 2 );
      }

      /* create listbox popup */

      lbeStyle = (LBS_NOTIFY | LBS_COMBOBOX | WS_BORDER | WS_CLIPSIBLINGS | WS_CHILD) |
                 (style & (WS_VSCROLL | CBS_OWNERDRAWFIXED | CBS_OWNERDRAWVARIABLE));

      if( lphc->dwStyle & CBS_SORT )
	lbeStyle |= LBS_SORT;
      if( lphc->dwStyle & CBS_HASSTRINGS )
	lbeStyle |= LBS_HASSTRINGS;
      if( lphc->dwStyle & CBS_NOINTEGRALHEIGHT )
	lbeStyle |= LBS_NOINTEGRALHEIGHT;
      if( lphc->dwStyle & CBS_DISABLENOSCROLL )
	lbeStyle |= LBS_DISABLENOSCROLL;

      if( CB_GETTYPE(lphc) == CBS_SIMPLE ) 	/* child listbox */
      {
	lbeStyle |= WS_VISIBLE;

	/*
	 * In win 95 look n feel, the listbox in the simple combobox has
	 * the WS_EXCLIENTEDGE style instead of the WS_BORDER style.
	 */
	lbeStyle   &= ~WS_BORDER;
	lbeExStyle |= WS_EX_CLIENTEDGE;
      }
      else
      {
        lbeExStyle |= (WS_EX_TOPMOST | WS_EX_TOOLWINDOW);
      }

      lphc->hWndLBox = CreateWindowExW(lbeExStyle, clbName, NULL, lbeStyle,
              lphc->droppedRect.left, lphc->droppedRect.top, lphc->droppedRect.right - lphc->droppedRect.left,
              lphc->droppedRect.bottom - lphc->droppedRect.top, hwnd, (HMENU)ID_CB_LISTBOX,
              (HINSTANCE)GetWindowLongPtrW( hwnd, GWLP_HINSTANCE ), lphc );
      if( lphc->hWndLBox )
      {
	  BOOL	bEdit = TRUE;
	  lbeStyle = WS_CHILD | WS_VISIBLE | ES_NOHIDESEL | ES_LEFT | ES_COMBO;

	  if( lphc->wState & CBF_EDIT )
	  {
	      if( lphc->dwStyle & CBS_OEMCONVERT )
		  lbeStyle |= ES_OEMCONVERT;
	      if( lphc->dwStyle & CBS_AUTOHSCROLL )
		  lbeStyle |= ES_AUTOHSCROLL;
	      if( lphc->dwStyle & CBS_LOWERCASE )
		  lbeStyle |= ES_LOWERCASE;
	      else if( lphc->dwStyle & CBS_UPPERCASE )
		  lbeStyle |= ES_UPPERCASE;

              if (!IsWindowEnabled(hwnd)) lbeStyle |= WS_DISABLED;

              lphc->hWndEdit = CreateWindowExW(0, editName, NULL, lbeStyle,
                                               lphc->textRect.left, lphc->textRect.top,
                                               lphc->textRect.right - lphc->textRect.left,
                                               lphc->textRect.bottom - lphc->textRect.top,
                                               hwnd, (HMENU)ID_CB_EDIT,
                                               (HINSTANCE)GetWindowLongPtrW( hwnd, GWLP_HINSTANCE ), NULL );
	      if( !lphc->hWndEdit )
		bEdit = FALSE;
	  }

          if( bEdit )
	  {
	    if( CB_GETTYPE(lphc) != CBS_SIMPLE )
	    {
              /* Now do the trick with parent */
	      SetParent(lphc->hWndLBox, HWND_DESKTOP);
              /*
               * If the combo is a dropdown, we must resize the control
	       * to fit only the text area and button. To do this,
	       * we send a dummy resize and the WM_WINDOWPOSCHANGING message
	       * will take care of setting the height for us.
               */
	      CBForceDummyResize(lphc);
	    }

	    TRACE("init done\n");
	    return 0;
	  }
	  ERR("edit control failure.\n");
      } else ERR("listbox failure.\n");
  } else ERR("no owner for visible combo.\n");

  /* CreateWindow() will send WM_NCDESTROY to cleanup */

  return -1;
}