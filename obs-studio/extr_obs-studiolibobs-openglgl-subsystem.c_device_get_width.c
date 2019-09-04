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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {TYPE_2__* cur_swap; } ;
typedef  TYPE_3__ gs_device_t ;
struct TYPE_5__ {int /*<<< orphan*/  cx; } ;
struct TYPE_6__ {TYPE_1__ info; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 

uint32_t device_get_width(const gs_device_t *device)
{
	if (device->cur_swap) {
		return device->cur_swap->info.cx;
	} else {
		blog(LOG_WARNING, "device_get_width (GL): No active swap");
		return 0;
	}
}