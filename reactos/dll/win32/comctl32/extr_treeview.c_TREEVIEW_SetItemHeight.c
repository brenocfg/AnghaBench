#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int uItemHeight; int dwStyle; int /*<<< orphan*/  bHeightSet; } ;
typedef  TYPE_1__ TREEVIEW_INFO ;
typedef  int LRESULT ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRACE (char*,int,...) ; 
 int /*<<< orphan*/  TREEVIEW_Invalidate (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int TREEVIEW_NaturalHeight (TYPE_1__*) ; 
 int /*<<< orphan*/  TREEVIEW_RecalculateVisibleOrder (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TREEVIEW_UpdateScrollBars (TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int TVS_NONEVENHEIGHT ; 

__attribute__((used)) static LRESULT
TREEVIEW_SetItemHeight(TREEVIEW_INFO *infoPtr, INT newHeight)
{
    INT prevHeight = infoPtr->uItemHeight;

    TRACE("new=%d, old=%d\n", newHeight, prevHeight);
    if (newHeight == -1)
    {
	infoPtr->uItemHeight = TREEVIEW_NaturalHeight(infoPtr);
	infoPtr->bHeightSet = FALSE;
    }
    else
    {
        if (newHeight == 0) newHeight = 1;
        infoPtr->uItemHeight = newHeight;
        infoPtr->bHeightSet = TRUE;
    }

    /* Round down, unless we support odd ("non even") heights. */
    if (!(infoPtr->dwStyle & TVS_NONEVENHEIGHT) && infoPtr->uItemHeight != 1)
    {
        infoPtr->uItemHeight &= ~1;
        TRACE("after rounding=%d\n", infoPtr->uItemHeight);
    }

    if (infoPtr->uItemHeight != prevHeight)
    {
	TREEVIEW_RecalculateVisibleOrder(infoPtr, NULL);
	TREEVIEW_UpdateScrollBars(infoPtr);
	TREEVIEW_Invalidate(infoPtr, NULL);
    }

    return prevHeight;
}