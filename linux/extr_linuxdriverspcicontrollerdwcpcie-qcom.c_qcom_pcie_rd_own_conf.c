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
struct pcie_port {int dummy; } ;
struct dw_pcie {scalar_t__ dbi_base; } ;

/* Variables and functions */
 int PCIBIOS_SUCCESSFUL ; 
 int PCI_CLASS_BRIDGE_PCI ; 
 int PCI_CLASS_REVISION ; 
 int dw_pcie_read (scalar_t__,int,int*) ; 
 int readl (scalar_t__) ; 
 struct dw_pcie* to_dw_pcie_from_pp (struct pcie_port*) ; 

__attribute__((used)) static int qcom_pcie_rd_own_conf(struct pcie_port *pp, int where, int size,
				 u32 *val)
{
	struct dw_pcie *pci = to_dw_pcie_from_pp(pp);

	/* the device class is not reported correctly from the register */
	if (where == PCI_CLASS_REVISION && size == 4) {
		*val = readl(pci->dbi_base + PCI_CLASS_REVISION);
		*val &= 0xff;	/* keep revision id */
		*val |= PCI_CLASS_BRIDGE_PCI << 16;
		return PCIBIOS_SUCCESSFUL;
	}

	return dw_pcie_read(pci->dbi_base + where, size, val);
}