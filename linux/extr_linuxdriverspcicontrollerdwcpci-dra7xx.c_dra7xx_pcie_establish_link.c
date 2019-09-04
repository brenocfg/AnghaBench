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
struct dw_pcie {int dbi_base; struct device* dev; } ;
struct dra7xx_pcie {int link_gen; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EXP_CAP_ID_OFFSET ; 
 int LTSSM_EN ; 
 int /*<<< orphan*/  PCIECTRL_DRA7XX_CONF_DEVICE_CMD ; 
 int PCI_EXP_LNKCAP ; 
 int PCI_EXP_LNKCAP_SLS ; 
 int PCI_EXP_LNKCAP_SLS_2_5GB ; 
 int PCI_EXP_LNKCTL2 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int dra7xx_pcie_readl (struct dra7xx_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dra7xx_pcie_writel (struct dra7xx_pcie*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ dw_pcie_link_up (struct dw_pcie*) ; 
 int /*<<< orphan*/  dw_pcie_read (int,int,int*) ; 
 int /*<<< orphan*/  dw_pcie_write (int,int,int) ; 
 struct dra7xx_pcie* to_dra7xx_pcie (struct dw_pcie*) ; 

__attribute__((used)) static int dra7xx_pcie_establish_link(struct dw_pcie *pci)
{
	struct dra7xx_pcie *dra7xx = to_dra7xx_pcie(pci);
	struct device *dev = pci->dev;
	u32 reg;
	u32 exp_cap_off = EXP_CAP_ID_OFFSET;

	if (dw_pcie_link_up(pci)) {
		dev_err(dev, "link is already up\n");
		return 0;
	}

	if (dra7xx->link_gen == 1) {
		dw_pcie_read(pci->dbi_base + exp_cap_off + PCI_EXP_LNKCAP,
			     4, &reg);
		if ((reg & PCI_EXP_LNKCAP_SLS) != PCI_EXP_LNKCAP_SLS_2_5GB) {
			reg &= ~((u32)PCI_EXP_LNKCAP_SLS);
			reg |= PCI_EXP_LNKCAP_SLS_2_5GB;
			dw_pcie_write(pci->dbi_base + exp_cap_off +
				      PCI_EXP_LNKCAP, 4, reg);
		}

		dw_pcie_read(pci->dbi_base + exp_cap_off + PCI_EXP_LNKCTL2,
			     2, &reg);
		if ((reg & PCI_EXP_LNKCAP_SLS) != PCI_EXP_LNKCAP_SLS_2_5GB) {
			reg &= ~((u32)PCI_EXP_LNKCAP_SLS);
			reg |= PCI_EXP_LNKCAP_SLS_2_5GB;
			dw_pcie_write(pci->dbi_base + exp_cap_off +
				      PCI_EXP_LNKCTL2, 2, reg);
		}
	}

	reg = dra7xx_pcie_readl(dra7xx, PCIECTRL_DRA7XX_CONF_DEVICE_CMD);
	reg |= LTSSM_EN;
	dra7xx_pcie_writel(dra7xx, PCIECTRL_DRA7XX_CONF_DEVICE_CMD, reg);

	return 0;
}