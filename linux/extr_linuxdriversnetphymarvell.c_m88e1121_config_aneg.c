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
struct phy_device {int /*<<< orphan*/  mdix_ctrl; } ;

/* Variables and functions */
 int genphy_config_aneg (struct phy_device*) ; 
 int genphy_soft_reset (struct phy_device*) ; 
 int m88e1121_config_aneg_rgmii_delays (struct phy_device*) ; 
 int marvell_set_polarity (struct phy_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ phy_interface_is_rgmii (struct phy_device*) ; 

__attribute__((used)) static int m88e1121_config_aneg(struct phy_device *phydev)
{
	int err = 0;

	if (phy_interface_is_rgmii(phydev)) {
		err = m88e1121_config_aneg_rgmii_delays(phydev);
		if (err < 0)
			return err;
	}

	err = genphy_soft_reset(phydev);
	if (err < 0)
		return err;

	err = marvell_set_polarity(phydev, phydev->mdix_ctrl);
	if (err < 0)
		return err;

	return genphy_config_aneg(phydev);
}