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
struct phy_device {int advertising; scalar_t__ autoneg; int supported; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int PHY_1000BT_FEATURES ; 
 int PHY_100BT_FEATURES ; 
 int PHY_10BT_FEATURES ; 
 int phy_config_aneg (struct phy_device*) ; 

int phy_speed_up(struct phy_device *phydev)
{
	u32 mask = PHY_10BT_FEATURES | PHY_100BT_FEATURES | PHY_1000BT_FEATURES;
	u32 adv_old = phydev->advertising;

	if (phydev->autoneg != AUTONEG_ENABLE)
		return 0;

	phydev->advertising = (adv_old & ~mask) | (phydev->supported & mask);

	if (phydev->advertising == adv_old)
		return 0;

	return phy_config_aneg(phydev);
}