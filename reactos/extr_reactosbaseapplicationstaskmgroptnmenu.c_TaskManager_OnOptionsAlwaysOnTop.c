#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  AlwaysOnTop; } ;
typedef  int /*<<< orphan*/  HMENU ;

/* Variables and functions */
 int /*<<< orphan*/  CheckMenuItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GWL_EXSTYLE ; 
 int /*<<< orphan*/  GetMenu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSubMenu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HWND_NOTOPMOST ; 
 int /*<<< orphan*/  HWND_TOPMOST ; 
 int /*<<< orphan*/  ID_OPTIONS_ALWAYSONTOP ; 
 int MF_BYCOMMAND ; 
 int MF_CHECKED ; 
 int MF_UNCHECKED ; 
 int /*<<< orphan*/  OPTIONS_MENU_INDEX ; 
 int SWP_NOMOVE ; 
 int SWP_NOSIZE ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__ TaskManagerSettings ; 
 int WS_EX_TOPMOST ; 
 int /*<<< orphan*/  hMainWnd ; 

void TaskManager_OnOptionsAlwaysOnTop(void)
{
    HMENU  hMenu;
    HMENU  hOptionsMenu;

    hMenu = GetMenu(hMainWnd);
    hOptionsMenu = GetSubMenu(hMenu, OPTIONS_MENU_INDEX);

    /*
     * Check or uncheck the always on top menu item
     * and update main window.
     */
    if ((GetWindowLongPtrW(hMainWnd, GWL_EXSTYLE) & WS_EX_TOPMOST) != 0)
    {
        CheckMenuItem(hOptionsMenu, ID_OPTIONS_ALWAYSONTOP, MF_BYCOMMAND|MF_UNCHECKED);
        TaskManagerSettings.AlwaysOnTop = FALSE;
        SetWindowPos(hMainWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
    }
    else
    {
        CheckMenuItem(hOptionsMenu, ID_OPTIONS_ALWAYSONTOP, MF_BYCOMMAND|MF_CHECKED);
        TaskManagerSettings.AlwaysOnTop = TRUE;
        SetWindowPos(hMainWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
    }
}