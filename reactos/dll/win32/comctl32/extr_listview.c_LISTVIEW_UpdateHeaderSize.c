#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int dwStyle; int /*<<< orphan*/  hwndHeader; int /*<<< orphan*/  hwndSelf; } ;
struct TYPE_8__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_7__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__ POINT ;
typedef  TYPE_3__ LISTVIEW_INFO ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  HWND_DESKTOP ; 
 int LVS_NOCOLUMNHEADER ; 
 int /*<<< orphan*/  MapWindowPoints (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int SWP_HIDEWINDOW ; 
 int SWP_NOACTIVATE ; 
 int SWP_NOZORDER ; 
 int SWP_SHOWWINDOW ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void LISTVIEW_UpdateHeaderSize(const LISTVIEW_INFO *infoPtr, INT nNewScrollPos)
{
    RECT winRect;
    POINT point[2];

    TRACE("nNewScrollPos=%d\n", nNewScrollPos);

    if (!infoPtr->hwndHeader)  return;

    GetWindowRect(infoPtr->hwndHeader, &winRect);
    point[0].x = winRect.left;
    point[0].y = winRect.top;
    point[1].x = winRect.right;
    point[1].y = winRect.bottom;

    MapWindowPoints(HWND_DESKTOP, infoPtr->hwndSelf, point, 2);
    point[0].x = -nNewScrollPos;
    point[1].x += nNewScrollPos;

    SetWindowPos(infoPtr->hwndHeader,0,
        point[0].x,point[0].y,point[1].x,point[1].y,
        (infoPtr->dwStyle & LVS_NOCOLUMNHEADER) ? SWP_HIDEWINDOW : SWP_SHOWWINDOW |
        SWP_NOZORDER | SWP_NOACTIVATE);
}