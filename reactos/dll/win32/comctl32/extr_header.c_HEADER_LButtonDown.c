#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_13__ {size_t x; size_t y; } ;
struct TYPE_14__ {int dwStyle; size_t iMoveItem; size_t xTrackOffset; size_t xOldTrack; int /*<<< orphan*/  hwndSelf; TYPE_2__* items; void* bTracking; void* bCaptured; TYPE_3__ ptLButtonDown; int /*<<< orphan*/  bDragging; void* bPressed; } ;
struct TYPE_11__ {size_t right; } ;
struct TYPE_12__ {size_t cxy; TYPE_1__ rect; void* bDown; } ;
typedef  TYPE_3__ POINT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  size_t INT ;
typedef  TYPE_4__ HEADER_INFO ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDI_WIDTH ; 
 int /*<<< orphan*/  HDN_BEGINTRACKW ; 
 int HDS_BUTTONS ; 
 int HDS_FULLDRAG ; 
 int /*<<< orphan*/  HEADER_DrawTrackLine (TYPE_4__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  HEADER_InternalHitTest (TYPE_4__*,TYPE_3__*,scalar_t__*,size_t*) ; 
 int /*<<< orphan*/  HEADER_RefreshItem (TYPE_4__*,size_t) ; 
 int /*<<< orphan*/  HEADER_SendNotifyWithIntFieldT (TYPE_4__*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ HHT_ONDIVIDER ; 
 scalar_t__ HHT_ONDIVOPEN ; 
 scalar_t__ HHT_ONHEADER ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetCapture (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,size_t) ; 
 void* TRUE ; 

__attribute__((used)) static LRESULT
HEADER_LButtonDown (HEADER_INFO *infoPtr, INT x, INT y)
{
    POINT pt;
    UINT  flags;
    INT   nItem;
    HDC   hdc;

    pt.x = x;
    pt.y = y;
    HEADER_InternalHitTest (infoPtr, &pt, &flags, &nItem);

    if ((infoPtr->dwStyle & HDS_BUTTONS) && (flags == HHT_ONHEADER)) {
	SetCapture (infoPtr->hwndSelf);
	infoPtr->bCaptured = TRUE;
	infoPtr->bPressed  = TRUE;
	infoPtr->bDragging = FALSE;
	infoPtr->iMoveItem = nItem;
	infoPtr->ptLButtonDown = pt;

	infoPtr->items[nItem].bDown = TRUE;

	/* Send WM_CUSTOMDRAW */
	hdc = GetDC (infoPtr->hwndSelf);
	HEADER_RefreshItem (infoPtr, nItem);
	ReleaseDC (infoPtr->hwndSelf, hdc);

	TRACE("Pressed item %d.\n", nItem);
    }
    else if ((flags == HHT_ONDIVIDER) || (flags == HHT_ONDIVOPEN)) {
        INT iCurrWidth = infoPtr->items[nItem].cxy;
        if (!HEADER_SendNotifyWithIntFieldT(infoPtr, HDN_BEGINTRACKW, nItem, HDI_WIDTH, iCurrWidth))
        {
	    SetCapture (infoPtr->hwndSelf);
	    infoPtr->bCaptured = TRUE;
	    infoPtr->bTracking = TRUE;
	    infoPtr->iMoveItem = nItem;
	    infoPtr->xTrackOffset = infoPtr->items[nItem].rect.right - pt.x;

	    if (!(infoPtr->dwStyle & HDS_FULLDRAG)) {
		infoPtr->xOldTrack = infoPtr->items[nItem].rect.right;
		hdc = GetDC (infoPtr->hwndSelf);
		HEADER_DrawTrackLine (infoPtr, hdc, infoPtr->xOldTrack);
		ReleaseDC (infoPtr->hwndSelf, hdc);
	    }

	    TRACE("Begin tracking item %d.\n", nItem);
	}
    }

    return 0;
}