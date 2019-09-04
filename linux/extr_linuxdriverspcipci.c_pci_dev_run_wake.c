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
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  pme_support; struct pci_bus* bus; } ;
struct pci_bus {int /*<<< orphan*/ * bridge; struct pci_bus* parent; struct pci_dev* self; } ;

/* Variables and functions */
 int device_can_wakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_pme_capable (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_target_state (struct pci_dev*,int) ; 

bool pci_dev_run_wake(struct pci_dev *dev)
{
	struct pci_bus *bus = dev->bus;

	if (!dev->pme_support)
		return false;

	/* PME-capable in principle, but not from the target power state */
	if (!pci_pme_capable(dev, pci_target_state(dev, true)))
		return false;

	if (device_can_wakeup(&dev->dev))
		return true;

	while (bus->parent) {
		struct pci_dev *bridge = bus->self;

		if (device_can_wakeup(&bridge->dev))
			return true;

		bus = bus->parent;
	}

	/* We have reached the root bus. */
	if (bus->bridge)
		return device_can_wakeup(bus->bridge);

	return false;
}