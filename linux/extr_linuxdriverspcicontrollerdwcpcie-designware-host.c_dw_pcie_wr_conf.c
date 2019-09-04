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
typedef  int /*<<< orphan*/  u32 ;
struct pcie_port {scalar_t__ root_bus_nr; } ;
struct pci_bus {scalar_t__ number; struct pcie_port* sysdata; } ;

/* Variables and functions */
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int /*<<< orphan*/  PCI_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_pcie_valid_device (struct pcie_port*,struct pci_bus*,int /*<<< orphan*/ ) ; 
 int dw_pcie_wr_other_conf (struct pcie_port*,struct pci_bus*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int dw_pcie_wr_own_conf (struct pcie_port*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dw_pcie_wr_conf(struct pci_bus *bus, u32 devfn,
			   int where, int size, u32 val)
{
	struct pcie_port *pp = bus->sysdata;

	if (!dw_pcie_valid_device(pp, bus, PCI_SLOT(devfn)))
		return PCIBIOS_DEVICE_NOT_FOUND;

	if (bus->number == pp->root_bus_nr)
		return dw_pcie_wr_own_conf(pp, where, size, val);

	return dw_pcie_wr_other_conf(pp, bus, devfn, where, size, val);
}