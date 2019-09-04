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
struct pci_dev {scalar_t__ has_secondary_link; } ;
struct pci_bus {struct pci_dev* self; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_SCAN_ALL_PCIE_DEVS ; 
 scalar_t__ pci_has_flag (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_is_pcie (struct pci_dev*) ; 

__attribute__((used)) static int only_one_child(struct pci_bus *bus)
{
	struct pci_dev *bridge = bus->self;

	/*
	 * Systems with unusual topologies set PCI_SCAN_ALL_PCIE_DEVS so
	 * we scan for all possible devices, not just Device 0.
	 */
	if (pci_has_flag(PCI_SCAN_ALL_PCIE_DEVS))
		return 0;

	/*
	 * A PCIe Downstream Port normally leads to a Link with only Device
	 * 0 on it (PCIe spec r3.1, sec 7.3.1).  As an optimization, scan
	 * only for Device 0 in that situation.
	 *
	 * Checking has_secondary_link is a hack to identify Downstream
	 * Ports because sometimes Switches are configured such that the
	 * PCIe Port Type labels are backwards.
	 */
	if (bridge && pci_is_pcie(bridge) && bridge->has_secondary_link)
		return 1;

	return 0;
}