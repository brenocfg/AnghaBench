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
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_5__ {scalar_t__ right; scalar_t__ left; scalar_t__ bottom; scalar_t__ top; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__ POINT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  GetCursorPos (TYPE_2__*) ; 
 int /*<<< orphan*/  GetDesktopWindow () ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  HWND_TOPMOST ; 
 int /*<<< orphan*/  SWP_NOSIZE ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VOID
OnTrayInitDialog(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam)
{
    POINT ptCursor;
    RECT rcWindow;
    RECT rcScreen;
    LONG x, y, cx, cy;

    GetCursorPos(&ptCursor);

    GetWindowRect(hwnd, &rcWindow);

    GetWindowRect(GetDesktopWindow(), &rcScreen);

    cx = rcWindow.right - rcWindow.left;
    cy = rcWindow.bottom - rcWindow.top;

    if (ptCursor.y + cy > rcScreen.bottom)
        y = ptCursor.y - cy;
    else
        y = ptCursor.y;

    if (ptCursor.x + cx > rcScreen.right)
        x = ptCursor.x - cx;
    else
        x = ptCursor.x;

    SetWindowPos(hwnd, HWND_TOPMOST, x, y, 0, 0, SWP_NOSIZE);
}