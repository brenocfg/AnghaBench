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
struct phy_device {scalar_t__ interface; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_88E1510_GEN_CTRL_REG_1 ; 
 int /*<<< orphan*/  MII_88E1510_GEN_CTRL_REG_1_MODE_MASK ; 
 int /*<<< orphan*/  MII_88E1510_GEN_CTRL_REG_1_MODE_SGMII ; 
 int /*<<< orphan*/  MII_88E1510_GEN_CTRL_REG_1_RESET ; 
 int MII_MARVELL_COPPER_PAGE ; 
 scalar_t__ PHY_INTERFACE_MODE_SGMII ; 
 int m88e1318_config_init (struct phy_device*) ; 
 int marvell_set_page (struct phy_device*,int) ; 
 int phy_modify (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int m88e1510_config_init(struct phy_device *phydev)
{
	int err;

	/* SGMII-to-Copper mode initialization */
	if (phydev->interface == PHY_INTERFACE_MODE_SGMII) {
		/* Select page 18 */
		err = marvell_set_page(phydev, 18);
		if (err < 0)
			return err;

		/* In reg 20, write MODE[2:0] = 0x1 (SGMII to Copper) */
		err = phy_modify(phydev, MII_88E1510_GEN_CTRL_REG_1,
				 MII_88E1510_GEN_CTRL_REG_1_MODE_MASK,
				 MII_88E1510_GEN_CTRL_REG_1_MODE_SGMII);
		if (err < 0)
			return err;

		/* PHY reset is necessary after changing MODE[2:0] */
		err = phy_modify(phydev, MII_88E1510_GEN_CTRL_REG_1, 0,
				 MII_88E1510_GEN_CTRL_REG_1_RESET);
		if (err < 0)
			return err;

		/* Reset page selection */
		err = marvell_set_page(phydev, MII_MARVELL_COPPER_PAGE);
		if (err < 0)
			return err;
	}

	return m88e1318_config_init(phydev);
}