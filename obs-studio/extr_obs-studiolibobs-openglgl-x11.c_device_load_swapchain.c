#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* wi; } ;
typedef  TYPE_3__ gs_swapchain_t ;
struct TYPE_10__ {TYPE_2__* plat; TYPE_3__* cur_swap; } ;
typedef  TYPE_4__ gs_device_t ;
typedef  int /*<<< orphan*/  XID ;
struct TYPE_8__ {int /*<<< orphan*/  pbuffer; int /*<<< orphan*/  context; int /*<<< orphan*/ * display; } ;
struct TYPE_7__ {int /*<<< orphan*/  window; } ;
typedef  int /*<<< orphan*/  GLXPbuffer ;
typedef  int /*<<< orphan*/  GLXContext ;
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  glXMakeContextCurrent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

extern void device_load_swapchain(gs_device_t *device, gs_swapchain_t *swap)
{
	if (device->cur_swap == swap)
		return;

	Display *dpy = device->plat->display;
	GLXContext ctx = device->plat->context;

	device->cur_swap = swap;

	if (swap) {
		XID window = swap->wi->window;
		if (!glXMakeContextCurrent(dpy, window, window, ctx)) {
			blog(LOG_ERROR, "Failed to make context current.");
		}
	} else {
		GLXPbuffer pbuf = device->plat->pbuffer;
		if (!glXMakeContextCurrent(dpy, pbuf, pbuf, ctx)) {
			blog(LOG_ERROR, "Failed to make context current.");
		}
	}
}