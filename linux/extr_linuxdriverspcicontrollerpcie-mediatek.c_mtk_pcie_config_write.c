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
struct pci_bus {int /*<<< orphan*/  number; } ;
struct mtk_pcie_port {int dummy; } ;

/* Variables and functions */
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 struct mtk_pcie_port* mtk_pcie_find_port (struct pci_bus*,unsigned int) ; 
 int mtk_pcie_hw_wr_cfg (struct mtk_pcie_port*,int /*<<< orphan*/ ,unsigned int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_pcie_config_write(struct pci_bus *bus, unsigned int devfn,
				 int where, int size, u32 val)
{
	struct mtk_pcie_port *port;
	u32 bn = bus->number;

	port = mtk_pcie_find_port(bus, devfn);
	if (!port)
		return PCIBIOS_DEVICE_NOT_FOUND;

	return mtk_pcie_hw_wr_cfg(port, bn, devfn, where, size, val);
}