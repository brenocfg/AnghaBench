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
struct miphy28lp_phy {scalar_t__ pipebase; int /*<<< orphan*/ * syscfg_reg; int /*<<< orphan*/  base; struct miphy28lp_dev* phydev; } ;
struct miphy28lp_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MIPHY_CTRL_DEFAULT ; 
 int /*<<< orphan*/  PCIE_CTRL_MASK ; 
 int /*<<< orphan*/  SATA_CTRL_MASK ; 
 int /*<<< orphan*/  SATA_CTRL_SELECT_PCIE ; 
 size_t SYSCFG_PCI ; 
 int /*<<< orphan*/  SYSCFG_PCIE_PCIE_VAL ; 
 size_t SYSCFG_SATA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int miphy28lp_configure_pcie (struct miphy28lp_phy*) ; 
 int miphy28lp_setup (struct miphy28lp_phy*,int /*<<< orphan*/ ) ; 
 int miphy_is_ready (struct miphy28lp_phy*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeb_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int miphy28lp_init_pcie(struct miphy28lp_phy *miphy_phy)
{
	struct miphy28lp_dev *miphy_dev = miphy_phy->phydev;
	int err;

	if ((!miphy_phy->syscfg_reg[SYSCFG_SATA]) ||
			(!miphy_phy->syscfg_reg[SYSCFG_PCI])
		|| (!miphy_phy->base) || (!miphy_phy->pipebase))
		return -EINVAL;

	dev_info(miphy_dev->dev, "pcie-up mode, addr 0x%p\n", miphy_phy->base);

	/* Configure the glue-logic */
	regmap_update_bits(miphy_dev->regmap,
			   miphy_phy->syscfg_reg[SYSCFG_SATA],
			   SATA_CTRL_MASK, SATA_CTRL_SELECT_PCIE);

	regmap_update_bits(miphy_dev->regmap, miphy_phy->syscfg_reg[SYSCFG_PCI],
			   PCIE_CTRL_MASK, SYSCFG_PCIE_PCIE_VAL);

	/* MiPHY path and clocking init */
	err = miphy28lp_setup(miphy_phy, MIPHY_CTRL_DEFAULT);

	if (err) {
		dev_err(miphy_dev->dev, "PCIe phy setup failed\n");
		return err;
	}

	/* initialize miphy */
	err = miphy28lp_configure_pcie(miphy_phy);
	if (err)
		return err;

	/* PIPE Wrapper Configuration */
	writeb_relaxed(0x68, miphy_phy->pipebase + 0x104); /* Rise_0 */
	writeb_relaxed(0x61, miphy_phy->pipebase + 0x105); /* Rise_1 */
	writeb_relaxed(0x68, miphy_phy->pipebase + 0x108); /* Fall_0 */
	writeb_relaxed(0x61, miphy_phy->pipebase + 0x109); /* Fall-1 */
	writeb_relaxed(0x68, miphy_phy->pipebase + 0x10c); /* Threshold_0 */
	writeb_relaxed(0x60, miphy_phy->pipebase + 0x10d); /* Threshold_1 */

	/* Wait for phy_ready */
	return miphy_is_ready(miphy_phy);
}