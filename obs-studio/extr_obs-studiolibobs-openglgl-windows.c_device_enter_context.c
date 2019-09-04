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
struct TYPE_11__ {TYPE_4__* plat; TYPE_3__* cur_swap; } ;
typedef  TYPE_5__ gs_device_t ;
struct TYPE_7__ {int /*<<< orphan*/  hdc; } ;
struct TYPE_10__ {int /*<<< orphan*/  hrc; TYPE_1__ window; } ;
struct TYPE_9__ {TYPE_2__* wi; } ;
struct TYPE_8__ {int /*<<< orphan*/  hdc; } ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wgl_make_current (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void device_enter_context(gs_device_t *device)
{
	HDC hdc = device->plat->window.hdc;
	if (device->cur_swap)
		hdc = device->cur_swap->wi->hdc;

	if (!wgl_make_current(hdc, device->plat->hrc))
		blog(LOG_ERROR, "device_enter_context (GL) failed");
}