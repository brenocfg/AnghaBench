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
struct phy_device {scalar_t__ autoneg; int /*<<< orphan*/  mdix_ctrl; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int /*<<< orphan*/  MII_M1111_PHY_LED_CONTROL ; 
 int /*<<< orphan*/  MII_M1111_PHY_LED_DIRECT ; 
 int genphy_config_aneg (struct phy_device*) ; 
 int genphy_soft_reset (struct phy_device*) ; 
 int marvell_set_polarity (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int m88e1111_config_aneg(struct phy_device *phydev)
{
	int err;

	/* The Marvell PHY has an errata which requires
	 * that certain registers get written in order
	 * to restart autonegotiation
	 */
	err = genphy_soft_reset(phydev);

	err = marvell_set_polarity(phydev, phydev->mdix_ctrl);
	if (err < 0)
		return err;

	err = phy_write(phydev, MII_M1111_PHY_LED_CONTROL,
			MII_M1111_PHY_LED_DIRECT);
	if (err < 0)
		return err;

	err = genphy_config_aneg(phydev);
	if (err < 0)
		return err;

	if (phydev->autoneg != AUTONEG_ENABLE) {
		/* A write to speed/duplex bits (that is performed by
		 * genphy_config_aneg() call above) must be followed by
		 * a software reset. Otherwise, the write has no effect.
		 */
		err = genphy_soft_reset(phydev);
		if (err < 0)
			return err;
	}

	return 0;
}