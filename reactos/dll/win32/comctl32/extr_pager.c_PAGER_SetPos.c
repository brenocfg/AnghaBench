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
struct TYPE_6__ {scalar_t__ nPos; int /*<<< orphan*/  hwndSelf; } ;
typedef  TYPE_1__ PAGER_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ PAGER_GetScrollRange (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGER_PositionChildWnd (TYPE_1__*) ; 
 int /*<<< orphan*/  PAGER_UpdateBtns (TYPE_1__*,scalar_t__,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static LRESULT
PAGER_SetPos(PAGER_INFO* infoPtr, INT newPos, BOOL fromBtnPress, BOOL calc_size)
{
    INT scrollRange = PAGER_GetScrollRange(infoPtr, calc_size);
    INT oldPos = infoPtr->nPos;

    if ((scrollRange <= 0) || (newPos < 0))
        infoPtr->nPos = 0;
    else if (newPos > scrollRange)
        infoPtr->nPos = scrollRange;
    else
        infoPtr->nPos = newPos;

    TRACE("[%p] pos=%d, oldpos=%d\n", infoPtr->hwndSelf, infoPtr->nPos, oldPos);

    if (infoPtr->nPos != oldPos)
    {
        /* gray and restore btns, and if from WM_SETPOS, hide the gray btns */
        PAGER_UpdateBtns(infoPtr, scrollRange, !fromBtnPress);
        PAGER_PositionChildWnd(infoPtr);
    }

    return 0;
}