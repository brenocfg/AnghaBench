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
struct TYPE_2__ {int /*<<< orphan*/  functional; int /*<<< orphan*/  enabled; } ;
struct acpi_device {int /*<<< orphan*/  handle; TYPE_1__ status; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  METHOD_NAME__CRS ; 
 int acpi_bus_get_status (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_walk_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_notifier_chain_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic_notifier_list ; 
 int /*<<< orphan*/  port ; 
 int /*<<< orphan*/  pvpanic_panic_nb ; 
 int /*<<< orphan*/  pvpanic_walk_resources ; 

__attribute__((used)) static int pvpanic_add(struct acpi_device *device)
{
	int ret;

	ret = acpi_bus_get_status(device);
	if (ret < 0)
		return ret;

	if (!device->status.enabled || !device->status.functional)
		return -ENODEV;

	acpi_walk_resources(device->handle, METHOD_NAME__CRS,
			    pvpanic_walk_resources, NULL);

	if (!port)
		return -ENODEV;

	atomic_notifier_chain_register(&panic_notifier_list,
				       &pvpanic_panic_nb);

	return 0;
}