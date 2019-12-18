#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int iItem; scalar_t__ lParam; int /*<<< orphan*/  mask; scalar_t__ iSubItem; } ;
struct TYPE_4__ {int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__* PLINE_INFO ;
typedef  TYPE_2__ LVITEMW ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  LVIF_PARAM ; 
 int /*<<< orphan*/  LVNI_SELECTED ; 
 scalar_t__ ListView_GetItem (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int ListView_GetNextItem (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

LPCWSTR GetValueName(HWND hwndLV, int iStartAt)
{
    int item;
    LVITEMW LVItem;
    PLINE_INFO lineinfo;

    /*
       if a new item is inserted, then no allocation,
       otherwise the heap block will be lost!
    */
    item = ListView_GetNextItem(hwndLV, iStartAt, LVNI_SELECTED);
    if (item == -1) return NULL;

    /*
        Should be always TRUE anyways
    */
    LVItem.iItem = item;
    LVItem.iSubItem = 0;
    LVItem.mask = LVIF_PARAM;
    if (ListView_GetItem(hwndLV, &LVItem) == FALSE)
        return NULL;

    lineinfo = (PLINE_INFO)LVItem.lParam;
    if (lineinfo == NULL)
        return NULL;

    return lineinfo->name;
}