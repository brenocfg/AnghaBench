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
struct phy_device {int lp_advertising; int supported; int advertising; scalar_t__ autoneg; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int PHY_1000BT_FEATURES ; 
 int PHY_100BT_FEATURES ; 
 int PHY_10BT_FEATURES ; 
 int phy_config_aneg (struct phy_device*) ; 
 int phy_poll_aneg_done (struct phy_device*) ; 

int phy_speed_down(struct phy_device *phydev, bool sync)
{
	u32 adv = phydev->lp_advertising & phydev->supported;
	u32 adv_old = phydev->advertising;
	int ret;

	if (phydev->autoneg != AUTONEG_ENABLE)
		return 0;

	if (adv & PHY_10BT_FEATURES)
		phydev->advertising &= ~(PHY_100BT_FEATURES |
					 PHY_1000BT_FEATURES);
	else if (adv & PHY_100BT_FEATURES)
		phydev->advertising &= ~PHY_1000BT_FEATURES;

	if (phydev->advertising == adv_old)
		return 0;

	ret = phy_config_aneg(phydev);
	if (ret)
		return ret;

	return sync ? phy_poll_aneg_done(phydev) : 0;
}