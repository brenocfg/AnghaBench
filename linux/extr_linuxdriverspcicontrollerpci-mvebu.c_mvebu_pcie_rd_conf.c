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
typedef  int u32 ;
struct pci_bus {scalar_t__ number; struct mvebu_pcie* sysdata; } ;
struct mvebu_pcie_port {int dummy; } ;
struct mvebu_pcie {int dummy; } ;

/* Variables and functions */
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 struct mvebu_pcie_port* mvebu_pcie_find_port (struct mvebu_pcie*,struct pci_bus*,int) ; 
 int mvebu_pcie_hw_rd_conf (struct mvebu_pcie_port*,struct pci_bus*,int,int,int,int*) ; 
 int /*<<< orphan*/  mvebu_pcie_link_up (struct mvebu_pcie_port*) ; 
 int mvebu_sw_pci_bridge_read (struct mvebu_pcie_port*,int,int,int*) ; 

__attribute__((used)) static int mvebu_pcie_rd_conf(struct pci_bus *bus, u32 devfn, int where,
			      int size, u32 *val)
{
	struct mvebu_pcie *pcie = bus->sysdata;
	struct mvebu_pcie_port *port;
	int ret;

	port = mvebu_pcie_find_port(pcie, bus, devfn);
	if (!port) {
		*val = 0xffffffff;
		return PCIBIOS_DEVICE_NOT_FOUND;
	}

	/* Access the emulated PCI-to-PCI bridge */
	if (bus->number == 0)
		return mvebu_sw_pci_bridge_read(port, where, size, val);

	if (!mvebu_pcie_link_up(port)) {
		*val = 0xffffffff;
		return PCIBIOS_DEVICE_NOT_FOUND;
	}

	/* Access the real PCIe interface */
	ret = mvebu_pcie_hw_rd_conf(port, bus, devfn,
				    where, size, val);

	return ret;
}