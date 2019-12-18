#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ nItemCount; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_1__ LISTVIEW_INFO ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 int /*<<< orphan*/  LISTVIEW_GetItemBox (TYPE_1__ const*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LISTVIEW_InvalidateRect (TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_redrawing (TYPE_1__ const*) ; 

__attribute__((used)) static inline void LISTVIEW_InvalidateItem(const LISTVIEW_INFO *infoPtr, INT nItem)
{
    RECT rcBox;

    if (!is_redrawing(infoPtr) || nItem < 0 || nItem >= infoPtr->nItemCount)
        return;

    LISTVIEW_GetItemBox(infoPtr, nItem, &rcBox);
    LISTVIEW_InvalidateRect(infoPtr, &rcBox);
}