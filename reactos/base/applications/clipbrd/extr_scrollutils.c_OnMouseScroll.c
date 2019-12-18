#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  WORD ;
typedef  scalar_t__ UINT ;
struct TYPE_4__ {scalar_t__ uLinesToScroll; scalar_t__ nPageY; scalar_t__ iWheelCarryoverY; scalar_t__ nPageX; scalar_t__ iWheelCarryoverX; } ;
typedef  TYPE_1__* LPSCROLLSTATE ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 scalar_t__ GET_WHEEL_DELTA_WPARAM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKELONG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OnScroll (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,TYPE_1__*) ; 
 scalar_t__ SB_HORZ ; 
 int /*<<< orphan*/  SB_LINEDOWN ; 
 int /*<<< orphan*/  SB_LINEUP ; 
 scalar_t__ SB_VERT ; 
 scalar_t__ WHEEL_DELTA ; 
 scalar_t__ WM_MOUSEHWHEEL ; 
 scalar_t__ WM_MOUSEWHEEL ; 
 int /*<<< orphan*/  assert (int) ; 

void OnMouseScroll(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LPSCROLLSTATE state)
{
    INT nBar;
    INT nPage;
    INT iDelta;
    UINT uLinesToScroll = state->uLinesToScroll;
    INT zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
    WORD sbCode;

    assert(uMsg == WM_MOUSEWHEEL || uMsg == WM_MOUSEHWHEEL);

    if (uMsg == WM_MOUSEWHEEL)
    {
        nBar = SB_VERT;
        nPage = state->nPageY;

        /* Accumulate wheel rotation ticks */
        zDelta += state->iWheelCarryoverY;
        state->iWheelCarryoverY = zDelta % WHEEL_DELTA;
    }
    else // if (uMsg == WM_MOUSEHWHEEL)
    {
        nBar = SB_HORZ;
        nPage = state->nPageX;

        /* Accumulate wheel rotation ticks */
        zDelta += state->iWheelCarryoverX;
        state->iWheelCarryoverX = zDelta % WHEEL_DELTA;
    }

    /*
     * If the user specified scrolling by pages, do so.
     * Due to a bug on Windows where, if the window height is
     * less than the scroll lines delta default value (== 3),
     * several lines would be skipped when scrolling if we
     * used the WHEEL_PAGESCROLL value. Instead of this, use
     * the number of lines per page as the limiting value.
     * See https://www.strchr.com/corrections_to_raymond_chen_s_wheel_scrolling_code
     * for more details.
     */
    if (uLinesToScroll > nPage) // (uLinesToScroll == WHEEL_PAGESCROLL)
        uLinesToScroll = nPage;
    /* If the user specified no wheel scrolling, don't do anything */
    else if (uLinesToScroll == 0)
        return;

    /* Compute the scroll direction and the absolute delta value */
    if (zDelta > 0)
    {
        sbCode = SB_LINEUP;
    }
    else
    {
        sbCode = SB_LINEDOWN;
        zDelta = -zDelta;
    }

    /* Compute how many lines we should scroll (in absolute value) */
    iDelta = (INT)uLinesToScroll * zDelta / WHEEL_DELTA;

    OnScroll(hWnd, nBar, MAKELONG(sbCode, 0), iDelta, state);
}