#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* plat; TYPE_3__* cur_swap; } ;
typedef  TYPE_4__ gs_device_t ;
typedef  int /*<<< orphan*/  XID ;
struct TYPE_8__ {TYPE_2__* wi; } ;
struct TYPE_7__ {int /*<<< orphan*/  window; } ;
struct TYPE_6__ {int /*<<< orphan*/  pbuffer; int /*<<< orphan*/ * display; int /*<<< orphan*/  context; } ;
typedef  int /*<<< orphan*/  GLXPbuffer ;
typedef  int /*<<< orphan*/  GLXContext ;
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  glXMakeContextCurrent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

extern void device_enter_context(gs_device_t *device)
{
	GLXContext context = device->plat->context;
	Display *display = device->plat->display;

	if (device->cur_swap) {
		XID window = device->cur_swap->wi->window;
		if (!glXMakeContextCurrent(display, window, window, context)) {
			blog(LOG_ERROR, "Failed to make context current.");
		}
	} else {
		GLXPbuffer pbuf = device->plat->pbuffer;
		if (!glXMakeContextCurrent(display, pbuf, pbuf, context)) {
			blog(LOG_ERROR, "Failed to make context current.");
		}
	}
}