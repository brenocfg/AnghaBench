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
typedef  scalar_t__ u8 ;
struct pci_dev {int dummy; } ;
struct pci_bus {int /*<<< orphan*/  self; } ;

/* Variables and functions */
 scalar_t__ PCI_EXP_TYPE_PCI_BRIDGE ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_bus_sem ; 
 struct pci_dev* pci_dev_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 scalar_t__ pci_is_pcie (struct pci_dev*) ; 
 scalar_t__ pci_pcie_type (struct pci_dev*) ; 
 scalar_t__ pcie_pme_walk_bus (struct pci_bus*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool pcie_pme_from_pci_bridge(struct pci_bus *bus, u8 devfn)
{
	struct pci_dev *dev;
	bool found = false;

	if (devfn)
		return false;

	dev = pci_dev_get(bus->self);
	if (!dev)
		return false;

	if (pci_is_pcie(dev) && pci_pcie_type(dev) == PCI_EXP_TYPE_PCI_BRIDGE) {
		down_read(&pci_bus_sem);
		if (pcie_pme_walk_bus(bus))
			found = true;
		up_read(&pci_bus_sem);
	}

	pci_dev_put(dev);
	return found;
}