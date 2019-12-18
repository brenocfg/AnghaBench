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
struct TYPE_5__ {size_t* order; TYPE_1__* items; } ;
struct TYPE_4__ {size_t iOrder; } ;
typedef  size_t INT ;
typedef  TYPE_1__ HEADER_ITEM ;
typedef  TYPE_2__ HEADER_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,size_t,size_t,size_t) ; 
 size_t max (size_t,size_t) ; 
 int /*<<< orphan*/  memmove (size_t*,size_t*,size_t) ; 
 size_t min (size_t,size_t) ; 

__attribute__((used)) static void
HEADER_ChangeItemOrder(const HEADER_INFO *infoPtr, INT iItem, INT iNewOrder)
{
    HEADER_ITEM *lpItem = &infoPtr->items[iItem];
    INT i, nMin, nMax;

    TRACE("%d: %d->%d\n", iItem, lpItem->iOrder, iNewOrder);
    if (lpItem->iOrder < iNewOrder)
    {
        memmove(&infoPtr->order[lpItem->iOrder],
               &infoPtr->order[lpItem->iOrder + 1],
               (iNewOrder - lpItem->iOrder) * sizeof(INT));
    }
    if (iNewOrder < lpItem->iOrder)
    {
        memmove(&infoPtr->order[iNewOrder + 1],
                &infoPtr->order[iNewOrder],
                (lpItem->iOrder - iNewOrder) * sizeof(INT));
    }
    infoPtr->order[iNewOrder] = iItem;
    nMin = min(lpItem->iOrder, iNewOrder);
    nMax = max(lpItem->iOrder, iNewOrder);
    for (i = nMin; i <= nMax; i++)
        infoPtr->items[infoPtr->order[i]].iOrder = i;
}