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
struct game_capture {int wait_for_target_startup; int /*<<< orphan*/ * next_window; } ;
typedef  int /*<<< orphan*/  mi ;
struct TYPE_7__ {scalar_t__ left; scalar_t__ right; scalar_t__ bottom; scalar_t__ top; } ;
struct TYPE_9__ {int cbSize; TYPE_1__ rcMonitor; int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {scalar_t__ left; scalar_t__ right; scalar_t__ bottom; scalar_t__ top; } ;
typedef  TYPE_2__ RECT ;
typedef  TYPE_3__ MONITORINFO ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HMONITOR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  GetForegroundWindow () ; 
 int /*<<< orphan*/  GetMonitorInfo (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ GetWindowLongPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  MONITOR_DEFAULTTONEAREST ; 
 int /*<<< orphan*/  MonitorFromRect (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int WS_BORDER ; 
 int WS_MAXIMIZE ; 
 int /*<<< orphan*/  setup_window (struct game_capture*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_fullscreen_window(struct game_capture *gc)
{
	HWND window = GetForegroundWindow();
	MONITORINFO mi = {0};
	HMONITOR monitor;
	DWORD styles;
	RECT rect;

	gc->next_window = NULL;

	if (!window) {
		return;
	}
	if (!GetWindowRect(window, &rect)) {
		return;
	}

	/* ignore regular maximized windows */
	styles = (DWORD)GetWindowLongPtr(window, GWL_STYLE);
	if ((styles & WS_MAXIMIZE) != 0 && (styles & WS_BORDER) != 0) {
		return;
	}

	monitor = MonitorFromRect(&rect, MONITOR_DEFAULTTONEAREST);
	if (!monitor) {
		return;
	}

	mi.cbSize = sizeof(mi);
	if (!GetMonitorInfo(monitor, &mi)) {
		return;
	}

	if (rect.left == mi.rcMonitor.left &&
	    rect.right == mi.rcMonitor.right &&
	    rect.bottom == mi.rcMonitor.bottom &&
	    rect.top == mi.rcMonitor.top) {
		setup_window(gc, window);
	} else {
		gc->wait_for_target_startup = true;
	}
}