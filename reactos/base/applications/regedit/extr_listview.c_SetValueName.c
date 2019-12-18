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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int /*<<< orphan*/ * psz; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ LVFINDINFOW ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  LVFI_STRING ; 
 int LVIS_FOCUSED ; 
 int LVIS_SELECTED ; 
 scalar_t__ ListView_FindItem (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 scalar_t__ ListView_GetItemCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ListView_SetItemState (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 scalar_t__ iListViewSelect ; 

VOID SetValueName(HWND hwndLV, LPCWSTR pszValueName)
{
    INT i, c;
    LVFINDINFOW fi;

    c = ListView_GetItemCount(hwndLV);
    for(i = 0; i < c; i++)
    {
        ListView_SetItemState(hwndLV, i, 0, LVIS_FOCUSED | LVIS_SELECTED);
    }
    if (pszValueName == NULL)
        i = 0;
    else
    {
        fi.flags    = LVFI_STRING;
        fi.psz      = pszValueName;
        i = ListView_FindItem(hwndLV, -1, &fi);
    }
    ListView_SetItemState(hwndLV, i, LVIS_FOCUSED | LVIS_SELECTED,
                          LVIS_FOCUSED | LVIS_SELECTED);
    iListViewSelect = i;
}