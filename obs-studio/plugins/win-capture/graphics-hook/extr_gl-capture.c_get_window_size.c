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
typedef  int uint32_t ;
struct TYPE_3__ {int right; int bottom; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  WindowFromDC (int /*<<< orphan*/ ) ; 
 scalar_t__ darkest_dungeon_fix ; 

__attribute__((used)) static void get_window_size(HDC hdc, uint32_t *cx, uint32_t *cy)
{
	HWND hwnd = WindowFromDC(hdc);
	RECT rc = {0};

	if (darkest_dungeon_fix) {
		*cx = 1920;
		*cy = 1080;
	} else {
		GetClientRect(hwnd, &rc);
		*cx = rc.right;
		*cy = rc.bottom;
	}
}