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
struct phy_device {scalar_t__ autoneg; int speed; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int BMCR_SPEED100 ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_SPECIAL_CONTROL_STATUS ; 
 int MII_SPEED_10 ; 
 int MII_SPEED_100 ; 
 int SPEED_10 ; 
 int SPEED_100 ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phydev_err (struct phy_device*,char*,int) ; 
 int rockchip_integrated_phy_analog_init (struct phy_device*) ; 

__attribute__((used)) static void rockchip_link_change_notify(struct phy_device *phydev)
{
	int speed = SPEED_10;

	if (phydev->autoneg == AUTONEG_ENABLE) {
		int reg = phy_read(phydev, MII_SPECIAL_CONTROL_STATUS);

		if (reg < 0) {
			phydev_err(phydev, "phy_read err: %d.\n", reg);
			return;
		}

		if (reg & MII_SPEED_100)
			speed = SPEED_100;
		else if (reg & MII_SPEED_10)
			speed = SPEED_10;
	} else {
		int bmcr = phy_read(phydev, MII_BMCR);

		if (bmcr < 0) {
			phydev_err(phydev, "phy_read err: %d.\n", bmcr);
			return;
		}

		if (bmcr & BMCR_SPEED100)
			speed = SPEED_100;
		else
			speed = SPEED_10;
	}

	/*
	 * If mode switch happens from 10BT to 100BT, all DSP/AFE
	 * registers are set to default values. So any AFE/DSP
	 * registers have to be re-initialized in this case.
	 */
	if ((phydev->speed == SPEED_10) && (speed == SPEED_100)) {
		int ret = rockchip_integrated_phy_analog_init(phydev);
		if (ret)
			phydev_err(phydev, "rockchip_integrated_phy_analog_init err: %d.\n",
				   ret);
	}
}