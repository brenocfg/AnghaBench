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
struct pci_bus {int /*<<< orphan*/ * bridge; struct pci_bus* parent; TYPE_1__* self; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ acpi_pm_device_can_wakeup (int /*<<< orphan*/ *) ; 
 int acpi_pm_set_bridge_wakeup (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int acpi_pci_propagate_wakeup(struct pci_bus *bus, bool enable)
{
	while (bus->parent) {
		if (acpi_pm_device_can_wakeup(&bus->self->dev))
			return acpi_pm_set_bridge_wakeup(&bus->self->dev, enable);

		bus = bus->parent;
	}

	/* We have reached the root bus. */
	if (bus->bridge) {
		if (acpi_pm_device_can_wakeup(bus->bridge))
			return acpi_pm_set_bridge_wakeup(bus->bridge, enable);
	}
	return 0;
}