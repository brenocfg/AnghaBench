#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ starting; scalar_t__ menu_is_active; } ;
struct TYPE_6__ {int bottom; int top; } ;
typedef  TYPE_1__ RECT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int GetMenuItemCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetMenuItemRect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  IsZoomed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RESIZE_VERT ; 
 int /*<<< orphan*/  SM_CYCAPTION ; 
 int /*<<< orphan*/  SM_CYFRAME ; 
 int /*<<< orphan*/  SM_CYMENU ; 
 TYPE_2__ gui ; 
 int /*<<< orphan*/  gui_set_shellsize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_winnt_3 () ; 
 int /*<<< orphan*/  s_hwnd ; 
 int /*<<< orphan*/  s_menuBar ; 

__attribute__((used)) static int
gui_mswin_get_menu_height(
    int	    fix_window)	    /* If TRUE, resize window if menu height changed */
{
    static int	old_menu_height = -1;

    RECT    rc1, rc2;
    int	    num;
    int	    menu_height;

    if (gui.menu_is_active)
	num = GetMenuItemCount(s_menuBar);
    else
	num = 0;

    if (num == 0)
	menu_height = 0;
    else
    {
	if (is_winnt_3())	/* for NT 3.xx */
	{
	    if (gui.starting)
		menu_height = GetSystemMetrics(SM_CYMENU);
	    else
	    {
		RECT r1, r2;
		int frameht = GetSystemMetrics(SM_CYFRAME);
		int capht = GetSystemMetrics(SM_CYCAPTION);

		/* get window rect of s_hwnd
		 * get client rect of s_hwnd
		 * get cap height
		 * subtract from window rect, the sum of client height,
		 * (if not maximized)frame thickness, and caption height.
		 */
		GetWindowRect(s_hwnd, &r1);
		GetClientRect(s_hwnd, &r2);
		menu_height = r1.bottom - r1.top - (r2.bottom - r2.top
				 + 2 * frameht * (!IsZoomed(s_hwnd)) + capht);
	    }
	}
	else			/* win95 and variants (NT 4.0, I guess) */
	{
	    /*
	     * In case 'lines' is set in _vimrc/_gvimrc window width doesn't
	     * seem to have been set yet, so menu wraps in default window
	     * width which is very narrow.  Instead just return height of a
	     * single menu item.  Will still be wrong when the menu really
	     * should wrap over more than one line.
	     */
	    GetMenuItemRect(s_hwnd, s_menuBar, 0, &rc1);
	    if (gui.starting)
		menu_height = rc1.bottom - rc1.top + 1;
	    else
	    {
		GetMenuItemRect(s_hwnd, s_menuBar, num - 1, &rc2);
		menu_height = rc2.bottom - rc1.top + 1;
	    }
	}
    }

    if (fix_window && menu_height != old_menu_height)
    {
	old_menu_height = menu_height;
	gui_set_shellsize(FALSE, FALSE, RESIZE_VERT);
    }

    return menu_height;
}