#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ valid; } ;
struct TYPE_4__ {unsigned int count; int /*<<< orphan*/ * handles; } ;
struct TYPE_6__ {scalar_t__ prepare_count; TYPE_2__ flags; TYPE_1__ resources; } ;
struct acpi_device {TYPE_3__ wakeup; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 int acpi_device_sleep_wake (struct acpi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int acpi_power_off_device (int /*<<< orphan*/ ,struct acpi_device*) ; 

int acpi_disable_wakeup_device_power(struct acpi_device *dev)
{
	unsigned int i;
	int err = 0;

	if (!dev || !dev->wakeup.flags.valid)
		return -1;

	//mutex_lock(&acpi_device_lock);

	if (--dev->wakeup.prepare_count > 0)
		goto out;

	/*
	 * Executing the code below even if prepare_count is already zero when
	 * the function is called may be useful, for example for initialisation.
	 */
	if (dev->wakeup.prepare_count < 0)
		dev->wakeup.prepare_count = 0;

	err = acpi_device_sleep_wake(dev, 0, 0, 0);
	if (err)
		goto out;

	/* Close power resource */
	for (i = 0; i < dev->wakeup.resources.count; i++) {
		int ret = acpi_power_off_device(
				dev->wakeup.resources.handles[i], dev);
		if (ret) {
			DPRINT("Transition power state\n");
			dev->wakeup.flags.valid = 0;
			err = -1;
			goto out;
		}
	}

 out:
	//mutex_unlock(&acpi_device_lock);
	return err;
}