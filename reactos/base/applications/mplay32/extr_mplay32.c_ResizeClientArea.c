#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_5__ {scalar_t__ top; scalar_t__ left; scalar_t__ bottom; scalar_t__ right; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__ POINT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  MoveWindow (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

void ResizeClientArea(HWND hwnd, int nWidth, int nHeight)
{
    RECT rcClientRect;
    RECT rcWindowRect;
    POINT ptDifference;

    GetClientRect(hwnd, &rcClientRect);
    GetWindowRect(hwnd, &rcWindowRect);
    ptDifference.x = (rcWindowRect.right - rcWindowRect.left) - rcClientRect.right;
    ptDifference.y = (rcWindowRect.bottom - rcWindowRect.top) - rcClientRect.bottom;
    MoveWindow(hwnd, rcWindowRect.left, rcWindowRect.top, nWidth + ptDifference.x, nHeight + ptDifference.y, TRUE);
}