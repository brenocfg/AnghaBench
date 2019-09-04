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
struct ls_pcie {struct dw_pcie* pci; } ;
struct dw_pcie {scalar_t__ dbi_base; } ;

/* Variables and functions */
 scalar_t__ PCI_HEADER_TYPE ; 
 int PCI_HEADER_TYPE_BRIDGE ; 
 int ioread8 (scalar_t__) ; 

__attribute__((used)) static bool ls_pcie_is_bridge(struct ls_pcie *pcie)
{
	struct dw_pcie *pci = pcie->pci;
	u32 header_type;

	header_type = ioread8(pci->dbi_base + PCI_HEADER_TYPE);
	header_type &= 0x7f;

	return header_type == PCI_HEADER_TYPE_BRIDGE;
}