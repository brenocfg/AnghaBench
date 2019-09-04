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
struct xilinx_pcie_port {scalar_t__ root_busno; } ;
struct pci_bus {scalar_t__ number; struct xilinx_pcie_port* sysdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  xilinx_pcie_link_up (struct xilinx_pcie_port*) ; 

__attribute__((used)) static bool xilinx_pcie_valid_device(struct pci_bus *bus, unsigned int devfn)
{
	struct xilinx_pcie_port *port = bus->sysdata;

	/* Check if link is up when trying to access downstream ports */
	if (bus->number != port->root_busno)
		if (!xilinx_pcie_link_up(port))
			return false;

	/* Only one device down on each root port */
	if (bus->number == port->root_busno && devfn > 0)
		return false;

	return true;
}