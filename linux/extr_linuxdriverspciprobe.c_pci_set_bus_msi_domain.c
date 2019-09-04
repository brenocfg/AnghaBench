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
struct pci_bus {int /*<<< orphan*/  dev; TYPE_1__* self; struct pci_bus* parent; } ;
struct irq_domain {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct irq_domain* dev_get_msi_domain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_msi_domain (int /*<<< orphan*/ *,struct irq_domain*) ; 
 struct irq_domain* pci_host_bridge_msi_domain (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_is_root_bus (struct pci_bus*) ; 

__attribute__((used)) static void pci_set_bus_msi_domain(struct pci_bus *bus)
{
	struct irq_domain *d;
	struct pci_bus *b;

	/*
	 * The bus can be a root bus, a subordinate bus, or a virtual bus
	 * created by an SR-IOV device.  Walk up to the first bridge device
	 * found or derive the domain from the host bridge.
	 */
	for (b = bus, d = NULL; !d && !pci_is_root_bus(b); b = b->parent) {
		if (b->self)
			d = dev_get_msi_domain(&b->self->dev);
	}

	if (!d)
		d = pci_host_bridge_msi_domain(b);

	dev_set_msi_domain(&bus->dev, d);
}