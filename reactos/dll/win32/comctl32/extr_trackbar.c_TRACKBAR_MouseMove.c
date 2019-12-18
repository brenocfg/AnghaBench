#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tme ;
struct TYPE_15__ {void* y; void* x; } ;
struct TYPE_14__ {int dwStyle; scalar_t__ lPos; int flags; int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/  rcThumb; } ;
struct TYPE_13__ {int cbSize; int /*<<< orphan*/  hwndTrack; int /*<<< orphan*/  dwFlags; } ;
typedef  TYPE_1__ TRACKMOUSEEVENT ;
typedef  TYPE_2__ TRACKBAR_INFO ;
typedef  TYPE_3__ POINT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  scalar_t__ LONG ;
typedef  void* INT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetWindowTheme (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PtInRect (int /*<<< orphan*/ *,TYPE_3__) ; 
 int TBS_VERT ; 
 int TB_AUTO_PAGE ; 
 int TB_DRAG_MODE ; 
 int TB_THUMBTRACK ; 
 int TB_THUMB_HOT ; 
 int /*<<< orphan*/  TME_CANCEL ; 
 int /*<<< orphan*/  TME_LEAVE ; 
 int /*<<< orphan*/  TRACE (char*,void*,void*) ; 
 int /*<<< orphan*/  TRACKBAR_AutoPage (TYPE_2__*,TYPE_3__) ; 
 scalar_t__ TRACKBAR_ConvertPlaceToPosition (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  TRACKBAR_InvalidateThumbMove (TYPE_2__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TRACKBAR_UpdateThumb (TYPE_2__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TrackMouseEvent (TYPE_1__*) ; 
 int /*<<< orphan*/  UpdateWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notify_with_scroll (TYPE_2__*,int) ; 

__attribute__((used)) static LRESULT
TRACKBAR_MouseMove (TRACKBAR_INFO *infoPtr, INT x, INT y)
{
    INT clickPlace = (infoPtr->dwStyle & TBS_VERT) ? y : x;
    LONG dragPos, oldPos = infoPtr->lPos;

    TRACE("(x=%d. y=%d)\n", x, y);

    if (infoPtr->flags & TB_AUTO_PAGE) {
	POINT pt;
	pt.x = x;
	pt.y = y;
	TRACKBAR_AutoPage (infoPtr, pt);
	return TRUE;
    }

    if (!(infoPtr->flags & TB_DRAG_MODE)) 
    {
        if (GetWindowTheme (infoPtr->hwndSelf))
        {
            DWORD oldFlags = infoPtr->flags;
            POINT pt;
            pt.x = x;
            pt.y = y;
            if (PtInRect (&infoPtr->rcThumb, pt))
            {
                TRACKMOUSEEVENT tme;
                tme.cbSize = sizeof( tme );
                tme.dwFlags = TME_LEAVE;
                tme.hwndTrack = infoPtr->hwndSelf;
                TrackMouseEvent( &tme );
                infoPtr->flags |= TB_THUMB_HOT;
            }
            else
            {
                TRACKMOUSEEVENT tme;
                tme.cbSize = sizeof( tme );
                tme.dwFlags = TME_CANCEL;
                tme.hwndTrack = infoPtr->hwndSelf;
                TrackMouseEvent( &tme );
                infoPtr->flags &= ~TB_THUMB_HOT; 
            }
            if (oldFlags != infoPtr->flags) InvalidateRect (infoPtr->hwndSelf, &infoPtr->rcThumb, FALSE);
        }
        return TRUE;
    }

    dragPos = TRACKBAR_ConvertPlaceToPosition (infoPtr, clickPlace);

    if (dragPos == oldPos) return TRUE;

    infoPtr->lPos = dragPos;
    TRACKBAR_UpdateThumb (infoPtr);

    notify_with_scroll (infoPtr, TB_THUMBTRACK | (infoPtr->lPos<<16));

    TRACKBAR_InvalidateThumbMove(infoPtr, oldPos, dragPos);
    UpdateWindow (infoPtr->hwndSelf);

    return TRUE;
}