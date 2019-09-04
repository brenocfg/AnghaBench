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
struct TYPE_3__ {int /*<<< orphan*/  cur_proj; int /*<<< orphan*/  proj_stack; } ;
typedef  TYPE_1__ gs_device_t ;

/* Variables and functions */
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void device_projection_push(gs_device_t *device)
{
	da_push_back(device->proj_stack, &device->cur_proj);
}