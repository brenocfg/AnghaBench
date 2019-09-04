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
struct rockchip_pcie {scalar_t__ root_bus_nr; } ;
struct pci_bus {scalar_t__ number; scalar_t__ primary; } ;

/* Variables and functions */

__attribute__((used)) static int rockchip_pcie_valid_device(struct rockchip_pcie *rockchip,
				      struct pci_bus *bus, int dev)
{
	/* access only one slot on each root port */
	if (bus->number == rockchip->root_bus_nr && dev > 0)
		return 0;

	/*
	 * do not read more than one device on the bus directly attached
	 * to RC's downstream side.
	 */
	if (bus->primary == rockchip->root_bus_nr && dev > 0)
		return 0;

	return 1;
}