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
struct miphy28lp_phy {int sata_gen; int /*<<< orphan*/ * syscfg_reg; int /*<<< orphan*/  base; struct miphy28lp_dev* phydev; } ;
struct miphy28lp_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MIPHY_CTRL_DEFAULT ; 
 int /*<<< orphan*/  PCIE_CTRL_MASK ; 
 int /*<<< orphan*/  SATA_CTRL_MASK ; 
 int SATA_CTRL_SELECT_PCIE ; 
 int SATA_CTRL_SELECT_SATA ; 
 int SATA_GEN1 ; 
 int SATA_SPDMODE ; 
 size_t SYSCFG_PCI ; 
 size_t SYSCFG_SATA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  miphy28lp_configure_sata (struct miphy28lp_phy*) ; 
 int miphy28lp_setup (struct miphy28lp_phy*,int /*<<< orphan*/ ) ; 
 int miphy_is_ready (struct miphy28lp_phy*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int miphy28lp_init_sata(struct miphy28lp_phy *miphy_phy)
{
	struct miphy28lp_dev *miphy_dev = miphy_phy->phydev;
	int err, sata_conf = SATA_CTRL_SELECT_SATA;

	if ((!miphy_phy->syscfg_reg[SYSCFG_SATA]) ||
			(!miphy_phy->syscfg_reg[SYSCFG_PCI]) ||
			(!miphy_phy->base))
		return -EINVAL;

	dev_info(miphy_dev->dev, "sata-up mode, addr 0x%p\n", miphy_phy->base);

	/* Configure the glue-logic */
	sata_conf |= ((miphy_phy->sata_gen - SATA_GEN1) << SATA_SPDMODE);

	regmap_update_bits(miphy_dev->regmap,
			   miphy_phy->syscfg_reg[SYSCFG_SATA],
			   SATA_CTRL_MASK, sata_conf);

	regmap_update_bits(miphy_dev->regmap, miphy_phy->syscfg_reg[SYSCFG_PCI],
			   PCIE_CTRL_MASK, SATA_CTRL_SELECT_PCIE);

	/* MiPHY path and clocking init */
	err = miphy28lp_setup(miphy_phy, MIPHY_CTRL_DEFAULT);

	if (err) {
		dev_err(miphy_dev->dev, "SATA phy setup failed\n");
		return err;
	}

	/* initialize miphy */
	miphy28lp_configure_sata(miphy_phy);

	return miphy_is_ready(miphy_phy);
}