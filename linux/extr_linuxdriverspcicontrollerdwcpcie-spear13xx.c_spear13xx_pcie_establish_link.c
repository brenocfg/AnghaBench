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
struct spear13xx_pcie {scalar_t__ is_gen1; struct pcie_app_reg* app_base; struct dw_pcie* pci; } ;
struct pcie_port {int dummy; } ;
struct pcie_app_reg {int /*<<< orphan*/  app_ctrl_0; } ;
struct dw_pcie {int dbi_base; int /*<<< orphan*/  dev; struct pcie_port pp; } ;

/* Variables and functions */
 int APP_LTSSM_ENABLE_ID ; 
 int DEVICE_TYPE_RC ; 
 int EXP_CAP_ID_OFFSET ; 
 int MISCTRL_EN_ID ; 
 int PCI_DEVICE_ID ; 
 int PCI_EXP_DEVCTL ; 
 int PCI_EXP_DEVCTL_READRQ ; 
 int PCI_EXP_LNKCAP ; 
 int PCI_EXP_LNKCAP_SLS ; 
 int PCI_EXP_LNKCAP_SLS_2_5GB ; 
 int PCI_EXP_LNKCTL2 ; 
 int PCI_VENDOR_ID ; 
 int REG_TRANSLATION_ENABLE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ dw_pcie_link_up (struct dw_pcie*) ; 
 int /*<<< orphan*/  dw_pcie_read (int,int,int*) ; 
 int /*<<< orphan*/  dw_pcie_setup_rc (struct pcie_port*) ; 
 int dw_pcie_wait_for_link (struct dw_pcie*) ; 
 int /*<<< orphan*/  dw_pcie_write (int,int,int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int spear13xx_pcie_establish_link(struct spear13xx_pcie *spear13xx_pcie)
{
	struct dw_pcie *pci = spear13xx_pcie->pci;
	struct pcie_port *pp = &pci->pp;
	struct pcie_app_reg *app_reg = spear13xx_pcie->app_base;
	u32 val;
	u32 exp_cap_off = EXP_CAP_ID_OFFSET;

	if (dw_pcie_link_up(pci)) {
		dev_err(pci->dev, "link already up\n");
		return 0;
	}

	dw_pcie_setup_rc(pp);

	/*
	 * this controller support only 128 bytes read size, however its
	 * default value in capability register is 512 bytes. So force
	 * it to 128 here.
	 */
	dw_pcie_read(pci->dbi_base + exp_cap_off + PCI_EXP_DEVCTL, 2, &val);
	val &= ~PCI_EXP_DEVCTL_READRQ;
	dw_pcie_write(pci->dbi_base + exp_cap_off + PCI_EXP_DEVCTL, 2, val);

	dw_pcie_write(pci->dbi_base + PCI_VENDOR_ID, 2, 0x104A);
	dw_pcie_write(pci->dbi_base + PCI_DEVICE_ID, 2, 0xCD80);

	/*
	 * if is_gen1 is set then handle it, so that some buggy card
	 * also works
	 */
	if (spear13xx_pcie->is_gen1) {
		dw_pcie_read(pci->dbi_base + exp_cap_off + PCI_EXP_LNKCAP,
			     4, &val);
		if ((val & PCI_EXP_LNKCAP_SLS) != PCI_EXP_LNKCAP_SLS_2_5GB) {
			val &= ~((u32)PCI_EXP_LNKCAP_SLS);
			val |= PCI_EXP_LNKCAP_SLS_2_5GB;
			dw_pcie_write(pci->dbi_base + exp_cap_off +
				      PCI_EXP_LNKCAP, 4, val);
		}

		dw_pcie_read(pci->dbi_base + exp_cap_off + PCI_EXP_LNKCTL2,
			     2, &val);
		if ((val & PCI_EXP_LNKCAP_SLS) != PCI_EXP_LNKCAP_SLS_2_5GB) {
			val &= ~((u32)PCI_EXP_LNKCAP_SLS);
			val |= PCI_EXP_LNKCAP_SLS_2_5GB;
			dw_pcie_write(pci->dbi_base + exp_cap_off +
				      PCI_EXP_LNKCTL2, 2, val);
		}
	}

	/* enable ltssm */
	writel(DEVICE_TYPE_RC | (1 << MISCTRL_EN_ID)
			| (1 << APP_LTSSM_ENABLE_ID)
			| ((u32)1 << REG_TRANSLATION_ENABLE),
			&app_reg->app_ctrl_0);

	return dw_pcie_wait_for_link(pci);
}