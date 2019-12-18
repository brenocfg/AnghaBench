#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int right; int left; } ;
struct TYPE_21__ {scalar_t__ uView; int nItemCount; int nItemWidth; int /*<<< orphan*/  hwndSelf; scalar_t__ hwndHeader; int /*<<< orphan*/  hdpaColumns; TYPE_1__ rcList; } ;
struct TYPE_20__ {int right; int left; } ;
struct TYPE_19__ {int cbSize; int nPage; int nMax; int fMask; int /*<<< orphan*/  nPos; } ;
typedef  TYPE_2__ SCROLLINFO ;
typedef  TYPE_3__ RECT ;
typedef  TYPE_4__ LISTVIEW_INFO ;
typedef  int INT ;

/* Variables and functions */
 scalar_t__ DPA_GetPtrCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetScrollInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int GetScrollPos (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDM_ORDERTOINDEX ; 
 int LISTVIEW_GetCountPerColumn (TYPE_4__*) ; 
 int /*<<< orphan*/  LISTVIEW_GetHeaderRect (TYPE_4__*,int,TYPE_3__*) ; 
 scalar_t__ LISTVIEW_GetViewRect (TYPE_4__*,TYPE_3__*) ; 
 scalar_t__ LISTVIEW_IsHeaderEnabled (TYPE_4__*) ; 
 int /*<<< orphan*/  LISTVIEW_UpdateHeaderSize (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LISTVIEW_UpdateSize (TYPE_4__*) ; 
 scalar_t__ LV_VIEW_DETAILS ; 
 scalar_t__ LV_VIEW_LIST ; 
 int /*<<< orphan*/  SB_HORZ ; 
 int SIF_PAGE ; 
 int SIF_POS ; 
 int SIF_RANGE ; 
 int SendMessageW (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ SetScrollInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 
 int debugscrollinfo (TYPE_2__*) ; 
 int max (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static INT LISTVIEW_UpdateHScroll(LISTVIEW_INFO *infoPtr)
{
    SCROLLINFO horzInfo;
    INT dx;

    ZeroMemory(&horzInfo, sizeof(SCROLLINFO));
    horzInfo.cbSize = sizeof(SCROLLINFO);
    horzInfo.nPage = infoPtr->rcList.right - infoPtr->rcList.left;

    /* for now, we'll set info.nMax to the _count_, and adjust it later */
    if (infoPtr->uView == LV_VIEW_LIST)
    {
	INT nPerCol = LISTVIEW_GetCountPerColumn(infoPtr);
	horzInfo.nMax = (infoPtr->nItemCount + nPerCol - 1) / nPerCol;

	/* scroll by at least one column per page */
	if(horzInfo.nPage < infoPtr->nItemWidth)
		horzInfo.nPage = infoPtr->nItemWidth;

	if (infoPtr->nItemWidth)
	    horzInfo.nPage /= infoPtr->nItemWidth;
    }
    else if (infoPtr->uView == LV_VIEW_DETAILS)
    {
	horzInfo.nMax = infoPtr->nItemWidth;
    }
    else /* LV_VIEW_ICON, or LV_VIEW_SMALLICON */
    {
	RECT rcView;

	if (LISTVIEW_GetViewRect(infoPtr, &rcView)) horzInfo.nMax = rcView.right - rcView.left;
    }

    if (LISTVIEW_IsHeaderEnabled(infoPtr))
    {
	if (DPA_GetPtrCount(infoPtr->hdpaColumns))
	{
	    RECT rcHeader;
	    INT index;

	    index = SendMessageW(infoPtr->hwndHeader, HDM_ORDERTOINDEX,
                                 DPA_GetPtrCount(infoPtr->hdpaColumns) - 1, 0);

	    LISTVIEW_GetHeaderRect(infoPtr, index, &rcHeader);
	    horzInfo.nMax = rcHeader.right;
	    TRACE("horzInfo.nMax=%d\n", horzInfo.nMax);
	}
    }

    horzInfo.fMask = SIF_RANGE | SIF_PAGE;
    horzInfo.nMax = max(horzInfo.nMax - 1, 0);
#ifdef __REACTOS__ /* CORE-16466 part 1 of 4 */
    horzInfo.nMax = (horzInfo.nPage == 0 ? 0 : horzInfo.nMax);
#endif
    dx = GetScrollPos(infoPtr->hwndSelf, SB_HORZ);
    dx -= SetScrollInfo(infoPtr->hwndSelf, SB_HORZ, &horzInfo, TRUE);
    TRACE("horzInfo=%s\n", debugscrollinfo(&horzInfo));

    /* Update the Header Control */
    if (infoPtr->hwndHeader)
    {
	horzInfo.fMask = SIF_POS;
	GetScrollInfo(infoPtr->hwndSelf, SB_HORZ, &horzInfo);
	LISTVIEW_UpdateHeaderSize(infoPtr, horzInfo.nPos);
    }

    LISTVIEW_UpdateSize(infoPtr);
    return dx;
}