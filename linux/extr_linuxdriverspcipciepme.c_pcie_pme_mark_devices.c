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
struct pci_dev {scalar_t__ subordinate; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_walk_bus (scalar_t__,int /*<<< orphan*/  (*) (struct pci_dev*,int /*<<< orphan*/ *),int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcie_pme_can_wakeup (struct pci_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pcie_pme_mark_devices(struct pci_dev *port)
{
	pcie_pme_can_wakeup(port, NULL);
	if (port->subordinate)
		pci_walk_bus(port->subordinate, pcie_pme_can_wakeup, NULL);
}