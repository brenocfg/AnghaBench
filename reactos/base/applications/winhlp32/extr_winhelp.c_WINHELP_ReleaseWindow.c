#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  hMainWnd; int /*<<< orphan*/  ref_count; } ;
typedef  TYPE_1__ WINHELP_WINDOW ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WINE_TRACE (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 

BOOL WINHELP_ReleaseWindow(WINHELP_WINDOW* win)
{
    WINE_TRACE("Release %p#%d--\n", win, win->ref_count);

    if (!--win->ref_count)
    {
        DestroyWindow(win->hMainWnd);
        return FALSE;
    }
    return TRUE;
}