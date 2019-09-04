#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pcie_port {TYPE_1__* mem; } ;
struct keystone_pcie {struct dw_pcie* pci; } ;
struct dw_pcie {struct pcie_port pp; } ;
struct TYPE_2__ {int start; int end; } ;

/* Variables and functions */
 int CFG_PCIM_WIN_CNT ; 
 int CFG_PCIM_WIN_SZ_IDX ; 
 int /*<<< orphan*/  CMD_STATUS ; 
 int /*<<< orphan*/  OB_OFFSET_HI (int) ; 
 int /*<<< orphan*/  OB_OFFSET_INDEX (int) ; 
 int /*<<< orphan*/  OB_SIZE ; 
 int OB_XLAT_EN_VAL ; 
 int /*<<< orphan*/  PCI_BASE_ADDRESS_0 ; 
 int /*<<< orphan*/  PCI_BASE_ADDRESS_1 ; 
 int SZ_1M ; 
 int /*<<< orphan*/  dw_pcie_writel_dbi (struct dw_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ks_dw_app_readl (struct keystone_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks_dw_app_writel (struct keystone_pcie*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ks_dw_pcie_clear_dbi_mode (struct keystone_pcie*) ; 
 int /*<<< orphan*/  ks_dw_pcie_set_dbi_mode (struct keystone_pcie*) ; 

void ks_dw_pcie_setup_rc_app_regs(struct keystone_pcie *ks_pcie)
{
	struct dw_pcie *pci = ks_pcie->pci;
	struct pcie_port *pp = &pci->pp;
	u32 start = pp->mem->start, end = pp->mem->end;
	int i, tr_size;
	u32 val;

	/* Disable BARs for inbound access */
	ks_dw_pcie_set_dbi_mode(ks_pcie);
	dw_pcie_writel_dbi(pci, PCI_BASE_ADDRESS_0, 0);
	dw_pcie_writel_dbi(pci, PCI_BASE_ADDRESS_1, 0);
	ks_dw_pcie_clear_dbi_mode(ks_pcie);

	/* Set outbound translation size per window division */
	ks_dw_app_writel(ks_pcie, OB_SIZE, CFG_PCIM_WIN_SZ_IDX & 0x7);

	tr_size = (1 << (CFG_PCIM_WIN_SZ_IDX & 0x7)) * SZ_1M;

	/* Using Direct 1:1 mapping of RC <-> PCI memory space */
	for (i = 0; (i < CFG_PCIM_WIN_CNT) && (start < end); i++) {
		ks_dw_app_writel(ks_pcie, OB_OFFSET_INDEX(i), start | 1);
		ks_dw_app_writel(ks_pcie, OB_OFFSET_HI(i), 0);
		start += tr_size;
	}

	/* Enable OB translation */
	val = ks_dw_app_readl(ks_pcie, CMD_STATUS);
	ks_dw_app_writel(ks_pcie, CMD_STATUS, OB_XLAT_EN_VAL | val);
}