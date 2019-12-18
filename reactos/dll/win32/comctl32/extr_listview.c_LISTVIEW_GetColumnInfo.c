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
struct TYPE_7__ {int /*<<< orphan*/  rcHeader; } ;
struct TYPE_6__ {int /*<<< orphan*/  hdpaColumns; scalar_t__ colRectsDirty; int /*<<< orphan*/  hwndHeader; } ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  TYPE_1__ LISTVIEW_INFO ;
typedef  scalar_t__ INT ;
typedef  TYPE_2__ COLUMN_INFO ;

/* Variables and functions */
 TYPE_2__* DPA_GetPtr (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ DPA_GetPtrCount (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  HDM_GETITEMRECT ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static inline COLUMN_INFO * LISTVIEW_GetColumnInfo(const LISTVIEW_INFO *infoPtr, INT nSubItem)
{
    static COLUMN_INFO mainItem;

    if (nSubItem == 0 && DPA_GetPtrCount(infoPtr->hdpaColumns) == 0) return &mainItem;
    assert (nSubItem >= 0 && nSubItem < DPA_GetPtrCount(infoPtr->hdpaColumns));

    /* update cached column rectangles */
    if (infoPtr->colRectsDirty)
    {
        COLUMN_INFO *info;
        LISTVIEW_INFO *Ptr = (LISTVIEW_INFO*)infoPtr;
        INT i;

        for (i = 0; i < DPA_GetPtrCount(infoPtr->hdpaColumns); i++) {
            info = DPA_GetPtr(infoPtr->hdpaColumns, i);
            SendMessageW(infoPtr->hwndHeader, HDM_GETITEMRECT, i, (LPARAM)&info->rcHeader);
        }
        Ptr->colRectsDirty = FALSE;
    }

    return DPA_GetPtr(infoPtr->hdpaColumns, nSubItem);
}