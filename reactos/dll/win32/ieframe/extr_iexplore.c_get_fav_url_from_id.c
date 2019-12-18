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
typedef  int /*<<< orphan*/  item ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int cbSize; int /*<<< orphan*/  dwItemData; int /*<<< orphan*/  fMask; } ;
typedef  TYPE_1__ MENUITEMINFOW ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/  HMENU ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetMenuItemInfoW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  MIIM_DATA ; 

__attribute__((used)) static LPWSTR get_fav_url_from_id(HMENU menu, UINT id)
{
    MENUITEMINFOW item;

    item.cbSize = sizeof(item);
    item.fMask = MIIM_DATA;

    if(!GetMenuItemInfoW(menu, id, FALSE, &item))
        return NULL;

    return (LPWSTR)item.dwItemData;
}