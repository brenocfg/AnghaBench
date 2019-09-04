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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct pci_epf_bar {int barno; } ;
struct pci_epc {int dummy; } ;
struct cdns_pcie {int dummy; } ;
struct cdns_pcie_ep {struct cdns_pcie pcie; } ;
typedef  enum pci_barno { ____Placeholder_pci_barno } pci_barno ;

/* Variables and functions */
 int BAR_4 ; 
 int CDNS_PCIE_AT_IB_EP_FUNC_BAR_ADDR0 (int /*<<< orphan*/ ,int) ; 
 int CDNS_PCIE_AT_IB_EP_FUNC_BAR_ADDR1 (int /*<<< orphan*/ ,int) ; 
 int CDNS_PCIE_LM_BAR_CFG_CTRL_DISABLED ; 
 int CDNS_PCIE_LM_EP_FUNC_BAR_CFG0 (int /*<<< orphan*/ ) ; 
 int CDNS_PCIE_LM_EP_FUNC_BAR_CFG1 (int /*<<< orphan*/ ) ; 
 int CDNS_PCIE_LM_EP_FUNC_BAR_CFG_BAR_APERTURE_MASK (int) ; 
 int CDNS_PCIE_LM_EP_FUNC_BAR_CFG_BAR_CTRL (int,int) ; 
 int CDNS_PCIE_LM_EP_FUNC_BAR_CFG_BAR_CTRL_MASK (int) ; 
 int cdns_pcie_readl (struct cdns_pcie*,int) ; 
 int /*<<< orphan*/  cdns_pcie_writel (struct cdns_pcie*,int,int) ; 
 struct cdns_pcie_ep* epc_get_drvdata (struct pci_epc*) ; 

__attribute__((used)) static void cdns_pcie_ep_clear_bar(struct pci_epc *epc, u8 fn,
				   struct pci_epf_bar *epf_bar)
{
	struct cdns_pcie_ep *ep = epc_get_drvdata(epc);
	struct cdns_pcie *pcie = &ep->pcie;
	enum pci_barno bar = epf_bar->barno;
	u32 reg, cfg, b, ctrl;

	if (bar < BAR_4) {
		reg = CDNS_PCIE_LM_EP_FUNC_BAR_CFG0(fn);
		b = bar;
	} else {
		reg = CDNS_PCIE_LM_EP_FUNC_BAR_CFG1(fn);
		b = bar - BAR_4;
	}

	ctrl = CDNS_PCIE_LM_BAR_CFG_CTRL_DISABLED;
	cfg = cdns_pcie_readl(pcie, reg);
	cfg &= ~(CDNS_PCIE_LM_EP_FUNC_BAR_CFG_BAR_APERTURE_MASK(b) |
		 CDNS_PCIE_LM_EP_FUNC_BAR_CFG_BAR_CTRL_MASK(b));
	cfg |= CDNS_PCIE_LM_EP_FUNC_BAR_CFG_BAR_CTRL(b, ctrl);
	cdns_pcie_writel(pcie, reg, cfg);

	cdns_pcie_writel(pcie, CDNS_PCIE_AT_IB_EP_FUNC_BAR_ADDR0(fn, bar), 0);
	cdns_pcie_writel(pcie, CDNS_PCIE_AT_IB_EP_FUNC_BAR_ADDR1(fn, bar), 0);
}