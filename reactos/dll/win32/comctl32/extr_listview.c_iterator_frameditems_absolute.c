#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {scalar_t__ lower; scalar_t__ upper; } ;
struct TYPE_25__ {int nSpecial; int /*<<< orphan*/  ranges; TYPE_3__ range; } ;
struct TYPE_21__ {int bottom; int top; } ;
struct TYPE_24__ {scalar_t__ nItemCount; scalar_t__ uView; int nFocusedItem; int nItemWidth; int nItemHeight; TYPE_1__ rcList; int /*<<< orphan*/  hdpaPosY; int /*<<< orphan*/  hdpaPosX; } ;
struct TYPE_22__ {int left; int top; int right; int bottom; } ;
typedef  TYPE_2__ RECT ;
typedef  int /*<<< orphan*/  RANGES ;
typedef  TYPE_3__ RANGE ;
typedef  void* LONG_PTR ;
typedef  TYPE_4__ LISTVIEW_INFO ;
typedef  TYPE_5__ ITERATOR ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ DPA_GetPtr (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IntersectRect (TYPE_2__*,TYPE_2__*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  LISTVIEW_GetItemBox (TYPE_4__ const*,int,TYPE_2__*) ; 
 scalar_t__ LV_VIEW_DETAILS ; 
 scalar_t__ LV_VIEW_ICON ; 
 scalar_t__ LV_VIEW_SMALLICON ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  debugrange (TYPE_3__*) ; 
 int /*<<< orphan*/  iterator_empty (TYPE_5__*) ; 
 int /*<<< orphan*/  iterator_rangeitems (TYPE_5__*,TYPE_3__) ; 
 int /*<<< orphan*/  iterator_rangesitems (TYPE_5__*,int /*<<< orphan*/ ) ; 
 void* max (int,int) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ranges_add (int /*<<< orphan*/ ,TYPE_3__) ; 
 int /*<<< orphan*/  ranges_additem (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ranges_create (scalar_t__) ; 
 int /*<<< orphan*/  wine_dbgstr_rect (TYPE_2__ const*) ; 

__attribute__((used)) static BOOL iterator_frameditems_absolute(ITERATOR* i, const LISTVIEW_INFO* infoPtr, const RECT *frame)
{
    RECT rcItem, rcTemp;
    RANGES ranges;

    TRACE("(frame=%s)\n", wine_dbgstr_rect(frame));

    /* in case we fail, we want to return an empty iterator */
    iterator_empty(i);

    if (infoPtr->nItemCount == 0)
        return TRUE;

    if (infoPtr->uView == LV_VIEW_ICON || infoPtr->uView == LV_VIEW_SMALLICON)
    {
	INT nItem;
	
	if (infoPtr->uView == LV_VIEW_ICON && infoPtr->nFocusedItem != -1)
	{
	    LISTVIEW_GetItemBox(infoPtr, infoPtr->nFocusedItem, &rcItem);
	    if (IntersectRect(&rcTemp, &rcItem, frame))
		i->nSpecial = infoPtr->nFocusedItem;
	}
	if (!(ranges = ranges_create(50))) return FALSE;
	iterator_rangesitems(i, ranges);
	/* to do better here, we need to have PosX, and PosY sorted */
	TRACE("building icon ranges:\n");
	for (nItem = 0; nItem < infoPtr->nItemCount; nItem++)
	{
            rcItem.left = (LONG_PTR)DPA_GetPtr(infoPtr->hdpaPosX, nItem);
	    rcItem.top = (LONG_PTR)DPA_GetPtr(infoPtr->hdpaPosY, nItem);
	    rcItem.right = rcItem.left + infoPtr->nItemWidth;
	    rcItem.bottom = rcItem.top + infoPtr->nItemHeight;
	    if (IntersectRect(&rcTemp, &rcItem, frame))
		ranges_additem(i->ranges, nItem);
	}
	return TRUE;
    }
    else if (infoPtr->uView == LV_VIEW_DETAILS)
    {
	RANGE range;
	
	if (frame->left >= infoPtr->nItemWidth) return TRUE;
	if (frame->top >= infoPtr->nItemHeight * infoPtr->nItemCount) return TRUE;
	
	range.lower = max(frame->top / infoPtr->nItemHeight, 0);
	range.upper = min((frame->bottom - 1) / infoPtr->nItemHeight, infoPtr->nItemCount - 1) + 1;
	if (range.upper <= range.lower) return TRUE;
	iterator_rangeitems(i, range);
	TRACE("    report=%s\n", debugrange(&i->range));
    }
    else
    {
	INT nPerCol = max((infoPtr->rcList.bottom - infoPtr->rcList.top) / infoPtr->nItemHeight, 1);
	INT nFirstRow = max(frame->top / infoPtr->nItemHeight, 0);
	INT nLastRow = min((frame->bottom - 1) / infoPtr->nItemHeight, nPerCol - 1);
	INT nFirstCol;
	INT nLastCol;
	INT lower;
	RANGE item_range;
	INT nCol;

	if (infoPtr->nItemWidth)
	{
	    nFirstCol = max(frame->left / infoPtr->nItemWidth, 0);
            nLastCol  = min((frame->right - 1) / infoPtr->nItemWidth, (infoPtr->nItemCount + nPerCol - 1) / nPerCol);
	}
	else
	{
	    nFirstCol = max(frame->left, 0);
            nLastCol  = min(frame->right - 1, (infoPtr->nItemCount + nPerCol - 1) / nPerCol);
	}

	lower = nFirstCol * nPerCol + nFirstRow;

	TRACE("nPerCol=%d, nFirstRow=%d, nLastRow=%d, nFirstCol=%d, nLastCol=%d, lower=%d\n",
	      nPerCol, nFirstRow, nLastRow, nFirstCol, nLastCol, lower);
	
	if (nLastCol < nFirstCol || nLastRow < nFirstRow) return TRUE;

	if (!(ranges = ranges_create(nLastCol - nFirstCol + 1))) return FALSE;
	iterator_rangesitems(i, ranges);
	TRACE("building list ranges:\n");
	for (nCol = nFirstCol; nCol <= nLastCol; nCol++)
	{
	    item_range.lower = nCol * nPerCol + nFirstRow;
	    if(item_range.lower >= infoPtr->nItemCount) break;
	    item_range.upper = min(nCol * nPerCol + nLastRow + 1, infoPtr->nItemCount);
	    TRACE("   list=%s\n", debugrange(&item_range));
	    ranges_add(i->ranges, item_range);
	}
    }

    return TRUE;
}