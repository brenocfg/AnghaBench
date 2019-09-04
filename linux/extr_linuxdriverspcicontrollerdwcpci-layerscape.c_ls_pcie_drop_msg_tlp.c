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
 scalar_t__ PCIE_STRFMR1 ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 

__attribute__((used)) static void ls_pcie_drop_msg_tlp(struct ls_pcie *pcie)
{
	u32 val;
	struct dw_pcie *pci = pcie->pci;

	val = ioread32(pci->dbi_base + PCIE_STRFMR1);
	val &= 0xDFFFFFFF;
	iowrite32(val, pci->dbi_base + PCIE_STRFMR1);
}