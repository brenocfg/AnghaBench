#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {void* y; void* x; } ;
struct TYPE_12__ {int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/  flags; int /*<<< orphan*/  lPos; int /*<<< orphan*/  rcThumb; } ;
typedef  TYPE_1__ TRACKBAR_INFO ;
typedef  TYPE_2__ POINT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  scalar_t__ LONG ;
typedef  void* INT ;

/* Variables and functions */
 scalar_t__ PtInRect (int /*<<< orphan*/ *,TYPE_2__) ; 
 int /*<<< orphan*/  SetCapture (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetFocus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTimer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TB_AUTO_PAGE_LEFT ; 
 int /*<<< orphan*/  TB_AUTO_PAGE_RIGHT ; 
 int /*<<< orphan*/  TB_DRAG_MODE ; 
 int /*<<< orphan*/  TB_REFRESH_DELAY ; 
 int /*<<< orphan*/  TB_REFRESH_TIMER ; 
 int /*<<< orphan*/  TRACKBAR_ActivateToolTip (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACKBAR_AutoPage (TYPE_1__*,TYPE_2__) ; 
 scalar_t__ TRACKBAR_GetAutoPageDirection (TYPE_1__*,TYPE_2__) ; 
 int /*<<< orphan*/  TRACKBAR_InvalidateThumb (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACKBAR_UpdateToolTip (TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static LRESULT
TRACKBAR_LButtonDown (TRACKBAR_INFO *infoPtr, INT x, INT y)
{
    POINT clickPoint;

    clickPoint.x = x;
    clickPoint.y = y;

    SetFocus(infoPtr->hwndSelf);

    if (PtInRect(&infoPtr->rcThumb, clickPoint)) {
        infoPtr->flags |= TB_DRAG_MODE;
        SetCapture (infoPtr->hwndSelf);
	TRACKBAR_UpdateToolTip (infoPtr);
	TRACKBAR_ActivateToolTip (infoPtr, TRUE);
	TRACKBAR_InvalidateThumb(infoPtr, infoPtr->lPos);
    } else {
	LONG dir = TRACKBAR_GetAutoPageDirection(infoPtr, clickPoint);
	if (dir == 0) return 0;
	infoPtr->flags |= (dir < 0) ? TB_AUTO_PAGE_LEFT : TB_AUTO_PAGE_RIGHT;
	TRACKBAR_AutoPage (infoPtr, clickPoint);
        SetCapture (infoPtr->hwndSelf);
        SetTimer(infoPtr->hwndSelf, TB_REFRESH_TIMER, TB_REFRESH_DELAY, 0);
    }

    return 0;
}