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
struct TYPE_2__ {int /*<<< orphan*/  HideWhenMinimized; } ;
typedef  int /*<<< orphan*/  HMENU ;

/* Variables and functions */
 int /*<<< orphan*/  CheckMenuItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetMenu (int /*<<< orphan*/ ) ; 
 int GetMenuState (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GetSubMenu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ID_OPTIONS_HIDEWHENMINIMIZED ; 
 int MF_BYCOMMAND ; 
 int MF_CHECKED ; 
 int MF_UNCHECKED ; 
 int /*<<< orphan*/  OPTIONS_MENU_INDEX ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__ TaskManagerSettings ; 
 int /*<<< orphan*/  hMainWnd ; 

void TaskManager_OnOptionsHideWhenMinimized(void)
{
    HMENU  hMenu;
    HMENU  hOptionsMenu;

    hMenu = GetMenu(hMainWnd);
    hOptionsMenu = GetSubMenu(hMenu, OPTIONS_MENU_INDEX);

    /*
     * Check or uncheck the hide when minimized menu item.
     */
    if (GetMenuState(hOptionsMenu, ID_OPTIONS_HIDEWHENMINIMIZED, MF_BYCOMMAND) & MF_CHECKED)
    {
        CheckMenuItem(hOptionsMenu, ID_OPTIONS_HIDEWHENMINIMIZED, MF_BYCOMMAND|MF_UNCHECKED);
        TaskManagerSettings.HideWhenMinimized = FALSE;
    }
    else
    {
        CheckMenuItem(hOptionsMenu, ID_OPTIONS_HIDEWHENMINIMIZED, MF_BYCOMMAND|MF_CHECKED);
        TaskManagerSettings.HideWhenMinimized = TRUE;
    }
}