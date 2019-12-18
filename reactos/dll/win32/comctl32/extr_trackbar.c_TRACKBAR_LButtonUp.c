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
struct TYPE_7__ {int flags; int lPos; int /*<<< orphan*/  hwndSelf; } ;
typedef  TYPE_1__ TRACKBAR_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KillTimer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NM_RELEASEDCAPTURE ; 
 int /*<<< orphan*/  ReleaseCapture () ; 
 int TB_AUTO_PAGE ; 
 int TB_DRAG_MODE ; 
 int TB_ENDTRACK ; 
 int /*<<< orphan*/  TB_REFRESH_TIMER ; 
 int TB_THUMBPOSITION ; 
 int /*<<< orphan*/  TRACKBAR_ActivateToolTip (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACKBAR_InvalidateThumb (TYPE_1__*,int) ; 
 int /*<<< orphan*/  notify (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notify_with_scroll (TYPE_1__*,int) ; 

__attribute__((used)) static LRESULT
TRACKBAR_LButtonUp (TRACKBAR_INFO *infoPtr)
{
    if (infoPtr->flags & TB_DRAG_MODE) {
        notify_with_scroll (infoPtr, TB_THUMBPOSITION | (infoPtr->lPos<<16));
        notify_with_scroll (infoPtr, TB_ENDTRACK);
        infoPtr->flags &= ~TB_DRAG_MODE;
        ReleaseCapture ();
	notify(infoPtr, NM_RELEASEDCAPTURE);
        TRACKBAR_ActivateToolTip(infoPtr, FALSE);
	TRACKBAR_InvalidateThumb(infoPtr, infoPtr->lPos);
    }
    if (infoPtr->flags & TB_AUTO_PAGE) {
	KillTimer (infoPtr->hwndSelf, TB_REFRESH_TIMER);
        infoPtr->flags &= ~TB_AUTO_PAGE;
        notify_with_scroll (infoPtr, TB_ENDTRACK);
        ReleaseCapture ();
	notify(infoPtr, NM_RELEASEDCAPTURE);
    }

    return 0;
}