#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int cbSize; scalar_t__ dwItemData; int /*<<< orphan*/  fMask; } ;
typedef  TYPE_1__ MENUITEMINFOW ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HMENU ;
typedef  int /*<<< orphan*/  CPlItem ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetMenu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetMenuItemInfoW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GetSubMenu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIIM_DATA ; 

__attribute__((used)) static CPlItem* Control_GetCPlItem_From_MenuID(HWND hWnd, UINT id)
{
    HMENU hMenu, hSubMenu;
    MENUITEMINFOW mii;

    /* retrieve the CPlItem structure from the menu item data */
    hMenu = GetMenu(hWnd);

    if (!hMenu)
        return NULL;

    hSubMenu = GetSubMenu(hMenu, 0);

    if (!hSubMenu)
        return NULL;

    mii.cbSize = sizeof(MENUITEMINFOW);
    mii.fMask = MIIM_DATA;

    if (!GetMenuItemInfoW(hSubMenu, id, FALSE, &mii))
        return NULL;

    return (CPlItem *) mii.dwItemData;
}