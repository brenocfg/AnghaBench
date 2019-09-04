#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct dasd_device {int /*<<< orphan*/  tasklet; int /*<<< orphan*/  tasklet_scheduled; } ;

/* Variables and functions */
 scalar_t__ atomic_cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dasd_get_device (struct dasd_device*) ; 
 int /*<<< orphan*/  tasklet_hi_schedule (int /*<<< orphan*/ *) ; 

void dasd_schedule_device_bh(struct dasd_device *device)
{
	/* Protect against rescheduling. */
	if (atomic_cmpxchg (&device->tasklet_scheduled, 0, 1) != 0)
		return;
	dasd_get_device(device);
	tasklet_hi_schedule(&device->tasklet);
}