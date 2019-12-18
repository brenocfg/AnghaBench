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
struct TYPE_4__ {int /*<<< orphan*/  last_drag_icon_rect; } ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_1__ DRAGLISTDATA ;

/* Variables and functions */
 int /*<<< orphan*/  DRAGLIST_TIMERID ; 
 int /*<<< orphan*/  GetParent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KillTimer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseCapture () ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void DragList_EndDrag(HWND hwnd, DRAGLISTDATA * data)
{
    KillTimer(hwnd, DRAGLIST_TIMERID);
    ReleaseCapture();
    /* clear any drag insert icon present */
    InvalidateRect(GetParent(hwnd), &data->last_drag_icon_rect, TRUE);
    /* clear data for next use */
    memset(data, 0, sizeof(*data));
}