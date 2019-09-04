#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rfkill_gpio_data {unsigned int type; } ;
struct device {TYPE_1__* driver; } ;
struct acpi_device_id {scalar_t__ driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  acpi_match_table; } ;

/* Variables and functions */
 int ENODEV ; 
 struct acpi_device_id* acpi_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  acpi_rfkill_default_gpios ; 
 int devm_acpi_dev_add_driver_gpios (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rfkill_gpio_acpi_probe(struct device *dev,
				  struct rfkill_gpio_data *rfkill)
{
	const struct acpi_device_id *id;

	id = acpi_match_device(dev->driver->acpi_match_table, dev);
	if (!id)
		return -ENODEV;

	rfkill->type = (unsigned)id->driver_data;

	return devm_acpi_dev_add_driver_gpios(dev, acpi_rfkill_default_gpios);
}