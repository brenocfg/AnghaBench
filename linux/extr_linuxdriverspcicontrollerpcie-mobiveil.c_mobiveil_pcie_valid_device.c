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
struct pci_bus {scalar_t__ number; scalar_t__ primary; struct mobiveil_pcie* sysdata; } ;
struct mobiveil_pcie {scalar_t__ root_bus_nr; } ;

/* Variables and functions */

__attribute__((used)) static bool mobiveil_pcie_valid_device(struct pci_bus *bus, unsigned int devfn)
{
	struct mobiveil_pcie *pcie = bus->sysdata;

	/* Only one device down on each root port */
	if ((bus->number == pcie->root_bus_nr) && (devfn > 0))
		return false;

	/*
	 * Do not read more than one device on the bus directly
	 * attached to RC
	 */
	if ((bus->primary == pcie->root_bus_nr) && (devfn > 0))
		return false;

	return true;
}