#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* cur_swap; } ;
typedef  TYPE_3__ gs_device_t ;
struct TYPE_6__ {TYPE_1__* wi; } ;
struct TYPE_5__ {int /*<<< orphan*/  hdc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  SwapBuffers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,...) ; 

void device_present(gs_device_t *device)
{
	if (!SwapBuffers(device->cur_swap->wi->hdc)) {
		blog(LOG_ERROR,
		     "SwapBuffers failed, GetLastError "
		     "returned %lu",
		     GetLastError());
		blog(LOG_ERROR, "device_present (GL) failed");
	}
}