#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ id; } ;
struct TYPE_5__ {int /*<<< orphan*/  hdpaItemIds; } ;
typedef  TYPE_1__ LISTVIEW_INFO ;
typedef  TYPE_2__ ITEM_ID ;
typedef  scalar_t__ INT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 TYPE_2__* DPA_GetPtr (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ DPA_GetPtrCount (int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD get_next_itemid(const LISTVIEW_INFO *infoPtr)
{
    INT count = DPA_GetPtrCount(infoPtr->hdpaItemIds);

    if (count > 0)
    {
        ITEM_ID *lpID = DPA_GetPtr(infoPtr->hdpaItemIds, count - 1);
        return lpID->id + 1;
    }
    return 0;
}