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
struct phy_device {int link; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int /*<<< orphan*/  MDIO_MMD_PHYXS ; 
 int /*<<< orphan*/  MDIO_MMD_VEND1 ; 
 int MDIO_PHYXS_LANE_READY ; 
 int MDIO_PHYXS_LNSTAT ; 
 int MDIO_STAT1 ; 
 int MDIO_STAT1_LSTATUS ; 
 int /*<<< orphan*/  SPEED_10000 ; 
 int phy_read_mmd (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int teranetics_read_status(struct phy_device *phydev)
{
	int reg;

	phydev->link = 1;

	phydev->speed = SPEED_10000;
	phydev->duplex = DUPLEX_FULL;

	if (!phy_read_mmd(phydev, MDIO_MMD_VEND1, 93)) {
		reg = phy_read_mmd(phydev, MDIO_MMD_PHYXS, MDIO_PHYXS_LNSTAT);
		if (reg < 0 ||
		    !((reg & MDIO_PHYXS_LANE_READY) == MDIO_PHYXS_LANE_READY)) {
			phydev->link = 0;
			return 0;
		}

		reg = phy_read_mmd(phydev, MDIO_MMD_AN, MDIO_STAT1);
		if (reg < 0 || !(reg & MDIO_STAT1_LSTATUS))
			phydev->link = 0;
	}

	return 0;
}