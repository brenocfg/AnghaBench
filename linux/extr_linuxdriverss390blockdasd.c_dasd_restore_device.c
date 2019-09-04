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
struct dasd_device {int /*<<< orphan*/  restore_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  dasd_get_device (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_put_device (struct dasd_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

void dasd_restore_device(struct dasd_device *device)
{
	dasd_get_device(device);
	/* queue call to dasd_restore_device to the kernel event daemon. */
	if (!schedule_work(&device->restore_device))
		dasd_put_device(device);
}