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
struct notifier_block {int dummy; } ;
struct device {int /*<<< orphan*/ * type; } ;

/* Variables and functions */
#define  BUS_NOTIFY_ADD_DEVICE 129 
#define  BUS_NOTIFY_REMOVED_DEVICE 128 
 int /*<<< orphan*/  chromeos_laptop_adjust_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chromeos_laptop_check_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chromeos_laptop_detach_i2c_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_adapter_type ; 
 int /*<<< orphan*/  i2c_client_type ; 
 int /*<<< orphan*/  to_i2c_adapter (struct device*) ; 
 int /*<<< orphan*/  to_i2c_client (struct device*) ; 

__attribute__((used)) static int chromeos_laptop_i2c_notifier_call(struct notifier_block *nb,
					     unsigned long action, void *data)
{
	struct device *dev = data;

	switch (action) {
	case BUS_NOTIFY_ADD_DEVICE:
		if (dev->type == &i2c_adapter_type)
			chromeos_laptop_check_adapter(to_i2c_adapter(dev));
		else if (dev->type == &i2c_client_type)
			chromeos_laptop_adjust_client(to_i2c_client(dev));
		break;

	case BUS_NOTIFY_REMOVED_DEVICE:
		if (dev->type == &i2c_client_type)
			chromeos_laptop_detach_i2c_client(to_i2c_client(dev));
		break;
	}

	return 0;
}