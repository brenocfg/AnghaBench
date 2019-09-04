#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int left; int top; int right; int bottom; } ;
typedef  TYPE_1__ RECT ;
typedef  scalar_t__ PRECT ;
typedef  int /*<<< orphan*/  POINT ;
typedef  int /*<<< orphan*/  LPPOINT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MapWindowPoints (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int SWP_NOACTIVATE ; 
 int SWP_NOOWNERZORDER ; 
 int SWP_NOSIZE ; 
 int SWP_NOZORDER ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int,int,int) ; 
 int /*<<< orphan*/  TRUE ; 

void AdjustFrameSize(HWND hCntrl, HWND hDlg, int nXDifference, int nYDifference, int pos)
{
    RECT  rc;
    int   cx, cy, sx, sy;

    GetClientRect(hCntrl, &rc);
    MapWindowPoints(hCntrl, hDlg, (LPPOINT)(PRECT)(&rc), sizeof(RECT)/sizeof(POINT));
    if (pos) {
        cx = rc.left;
        cy = rc.top;
        sx = rc.right - rc.left;
        switch (pos) {
        case 1:
            break;
        case 2:
            cy += nYDifference / 2;
            break;
        case 3:
            sx += nXDifference;
            break;
        case 4:
            cy += nYDifference / 2;
            sx += nXDifference;
            break;
        }
        sy = rc.bottom - rc.top + nYDifference / 2;
        SetWindowPos(hCntrl, NULL, cx, cy, sx, sy, SWP_NOACTIVATE|SWP_NOOWNERZORDER|SWP_NOZORDER);
    } else {
        cx = rc.left + nXDifference;
        cy = rc.top + nYDifference;
        SetWindowPos(hCntrl, NULL, cx, cy, 0, 0, SWP_NOACTIVATE|SWP_NOOWNERZORDER|SWP_NOSIZE|SWP_NOZORDER);
    }
    InvalidateRect(hCntrl, NULL, TRUE);
}