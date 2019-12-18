#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tme ;
typedef  int UINT ;
struct TYPE_29__ {scalar_t__ left; scalar_t__ right; } ;
struct TYPE_28__ {int dwStyle; scalar_t__ iHotItem; size_t iMoveItem; scalar_t__ xTrackOffset; scalar_t__ xOldTrack; int /*<<< orphan*/  hwndSelf; void* bDragging; TYPE_4__* items; scalar_t__ bTracking; scalar_t__ bPressed; scalar_t__ bCaptured; } ;
struct TYPE_27__ {scalar_t__ bDown; TYPE_9__ rect; scalar_t__ cxy; } ;
struct TYPE_26__ {scalar_t__ x; scalar_t__ y; } ;
struct TYPE_25__ {scalar_t__ left; } ;
struct TYPE_24__ {int cbSize; int /*<<< orphan*/  hwndTrack; int /*<<< orphan*/  dwFlags; } ;
typedef  TYPE_1__ TRACKMOUSEEVENT ;
typedef  scalar_t__ SHORT ;
typedef  TYPE_2__ RECT ;
typedef  TYPE_3__ POINT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/ * HIMAGELIST ;
typedef  TYPE_4__ HEADER_ITEM ;
typedef  TYPE_5__ HEADER_INFO ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ClientToScreen (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GetWindowTheme (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDI_WIDTH ; 
 int /*<<< orphan*/  HDN_BEGINDRAG ; 
 int /*<<< orphan*/  HDN_ITEMCHANGEDW ; 
 int /*<<< orphan*/  HDN_ITEMCHANGINGW ; 
 int /*<<< orphan*/  HDN_TRACKW ; 
 int HDS_BUTTONS ; 
 int HDS_DRAGDROP ; 
 int HDS_FULLDRAG ; 
 int HDS_HOTTRACK ; 
 int /*<<< orphan*/ * HEADER_CreateDragImage (TYPE_5__*,size_t) ; 
 int /*<<< orphan*/  HEADER_DrawTrackLine (TYPE_5__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HEADER_InternalHitTest (TYPE_5__*,TYPE_3__*,int*,scalar_t__*) ; 
 scalar_t__ HEADER_IsDragDistance (TYPE_5__*,TYPE_3__*) ; 
 int /*<<< orphan*/  HEADER_RefreshItem (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  HEADER_SendNotifyWithHDItemT (TYPE_5__*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEADER_SendNotifyWithIntFieldT (TYPE_5__*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HEADER_SetHotDivider (TYPE_5__*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEADER_SetItemBounds (TYPE_5__*) ; 
 int HHT_ONDIVIDER ; 
 int HHT_ONDIVOPEN ; 
 int HHT_ONHEADER ; 
 scalar_t__ HIWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ImageList_BeginDrag (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ImageList_Destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ImageList_DragMove (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ImageList_DragShowNolock (void*) ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,TYPE_9__*,scalar_t__) ; 
 scalar_t__ LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScrollWindowEx (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TME_LEAVE ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 void* TRUE ; 
 int /*<<< orphan*/  TrackMouseEvent (TYPE_1__*) ; 
 int /*<<< orphan*/  UpdateWindow (int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT
HEADER_MouseMove (HEADER_INFO *infoPtr, LPARAM lParam)
{
    POINT pt;
    UINT  flags;
    INT   nItem, nWidth;
    HDC   hdc;
    /* With theming, hottracking is always enabled */
    BOOL  hotTrackEnabled =
        ((infoPtr->dwStyle & HDS_BUTTONS) && (infoPtr->dwStyle & HDS_HOTTRACK))
        || (GetWindowTheme (infoPtr->hwndSelf) != NULL);
    INT oldHotItem = infoPtr->iHotItem;

    pt.x = (INT)(SHORT)LOWORD(lParam);
    pt.y = (INT)(SHORT)HIWORD(lParam);
    HEADER_InternalHitTest (infoPtr, &pt, &flags, &nItem);

    if (hotTrackEnabled) {
	if (flags & (HHT_ONHEADER | HHT_ONDIVIDER | HHT_ONDIVOPEN))
	    infoPtr->iHotItem = nItem;
	else
	    infoPtr->iHotItem = -1;
    }

    if (infoPtr->bCaptured) {
        /* check if we should drag the header */
	if (infoPtr->bPressed && !infoPtr->bDragging && (infoPtr->dwStyle & HDS_DRAGDROP)
	    && HEADER_IsDragDistance(infoPtr, &pt))
	{
            if (!HEADER_SendNotifyWithHDItemT(infoPtr, HDN_BEGINDRAG, infoPtr->iMoveItem, NULL))
	    {
		HIMAGELIST hDragItem = HEADER_CreateDragImage(infoPtr, infoPtr->iMoveItem);
		if (hDragItem != NULL)
		{
		    HEADER_ITEM *lpItem = &infoPtr->items[infoPtr->iMoveItem];
		    TRACE("Starting item drag\n");
		    ImageList_BeginDrag(hDragItem, 0, pt.x - lpItem->rect.left, 0);
		    ImageList_DragShowNolock(TRUE);
		    ImageList_Destroy(hDragItem);
		    infoPtr->bDragging = TRUE;
		}
	    }
	}
	
	if (infoPtr->bDragging)
	{
	    POINT drag;
	    drag.x = pt.x;
	    drag.y = 0;
	    ClientToScreen(infoPtr->hwndSelf, &drag);
	    ImageList_DragMove(drag.x, drag.y);
	    HEADER_SetHotDivider(infoPtr, TRUE, lParam);
	}
	
	if (infoPtr->bPressed && !infoPtr->bDragging) {
            BOOL oldState = infoPtr->items[infoPtr->iMoveItem].bDown;
	    if ((nItem == infoPtr->iMoveItem) && (flags == HHT_ONHEADER))
		infoPtr->items[infoPtr->iMoveItem].bDown = TRUE;
	    else
		infoPtr->items[infoPtr->iMoveItem].bDown = FALSE;
            if (oldState != infoPtr->items[infoPtr->iMoveItem].bDown) {
                hdc = GetDC (infoPtr->hwndSelf);
	        HEADER_RefreshItem (infoPtr, infoPtr->iMoveItem);
	        ReleaseDC (infoPtr->hwndSelf, hdc);
            }

	    TRACE("Moving pressed item %d.\n", infoPtr->iMoveItem);
	}
	else if (infoPtr->bTracking) {
	    if (infoPtr->dwStyle & HDS_FULLDRAG) {
                HEADER_ITEM *lpItem = &infoPtr->items[infoPtr->iMoveItem];
                nWidth = pt.x - lpItem->rect.left + infoPtr->xTrackOffset;
                if (!HEADER_SendNotifyWithIntFieldT(infoPtr, HDN_ITEMCHANGINGW, infoPtr->iMoveItem, HDI_WIDTH, nWidth))
		{
                    INT nOldWidth = lpItem->rect.right - lpItem->rect.left;
                    RECT rcClient;
                    RECT rcScroll;
                    
                    if (nWidth < 0) nWidth = 0;
                    infoPtr->items[infoPtr->iMoveItem].cxy = nWidth;
                    HEADER_SetItemBounds(infoPtr);
                    
                    GetClientRect(infoPtr->hwndSelf, &rcClient);
                    rcScroll = rcClient;
                    rcScroll.left = lpItem->rect.left + nOldWidth;
                    ScrollWindowEx(infoPtr->hwndSelf, nWidth - nOldWidth, 0, &rcScroll, &rcClient, NULL, NULL, 0);
                    InvalidateRect(infoPtr->hwndSelf, &lpItem->rect, FALSE);
                    UpdateWindow(infoPtr->hwndSelf);
                    
                    HEADER_SendNotifyWithIntFieldT(infoPtr, HDN_ITEMCHANGEDW, infoPtr->iMoveItem, HDI_WIDTH, nWidth);
		}
	    }
	    else {
                INT iTrackWidth;
		hdc = GetDC (infoPtr->hwndSelf);
		HEADER_DrawTrackLine (infoPtr, hdc, infoPtr->xOldTrack);
		infoPtr->xOldTrack = pt.x + infoPtr->xTrackOffset;
		if (infoPtr->xOldTrack < infoPtr->items[infoPtr->iMoveItem].rect.left)
		    infoPtr->xOldTrack = infoPtr->items[infoPtr->iMoveItem].rect.left;
		HEADER_DrawTrackLine (infoPtr, hdc, infoPtr->xOldTrack);
		ReleaseDC (infoPtr->hwndSelf, hdc);
                iTrackWidth = infoPtr->xOldTrack - infoPtr->items[infoPtr->iMoveItem].rect.left;
                /* FIXME: should stop tracking if HDN_TRACK returns TRUE */
                HEADER_SendNotifyWithIntFieldT(infoPtr, HDN_TRACKW, infoPtr->iMoveItem, HDI_WIDTH, iTrackWidth);
	    }

	    TRACE("Tracking item %d.\n", infoPtr->iMoveItem);
	}
    }

    if (hotTrackEnabled) {
        TRACKMOUSEEVENT tme;
        if (oldHotItem != infoPtr->iHotItem && !infoPtr->bDragging) {
	    hdc = GetDC (infoPtr->hwndSelf);
	    if (oldHotItem != -1) HEADER_RefreshItem (infoPtr, oldHotItem);
	    if (infoPtr->iHotItem != -1) HEADER_RefreshItem (infoPtr, infoPtr->iHotItem);
	    ReleaseDC (infoPtr->hwndSelf, hdc);
        }
        tme.cbSize = sizeof( tme );
        tme.dwFlags = TME_LEAVE;
        tme.hwndTrack = infoPtr->hwndSelf;
        TrackMouseEvent( &tme );
    }

    return 0;
}