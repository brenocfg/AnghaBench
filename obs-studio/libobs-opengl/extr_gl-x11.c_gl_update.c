#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_window_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_11__ {TYPE_4__* cur_swap; TYPE_1__* plat; } ;
typedef  TYPE_5__ gs_device_t ;
struct TYPE_9__ {int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; } ;
struct TYPE_10__ {TYPE_3__ info; TYPE_2__* wi; } ;
struct TYPE_8__ {int /*<<< orphan*/  window; } ;
struct TYPE_7__ {int /*<<< orphan*/ * display; } ;
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 int XCB_CONFIG_WINDOW_HEIGHT ; 
 int XCB_CONFIG_WINDOW_WIDTH ; 
 int /*<<< orphan*/  XGetXCBConnection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_configure_window (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

extern void gl_update(gs_device_t *device)
{
	Display *display = device->plat->display;
	xcb_window_t window = device->cur_swap->wi->window;

	uint32_t values[] = {device->cur_swap->info.cx,
			     device->cur_swap->info.cy};

	xcb_configure_window(XGetXCBConnection(display), window,
			     XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT,
			     values);
}