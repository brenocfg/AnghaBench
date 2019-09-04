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
 int MDIO_STAT1 ; 
 int MDIO_STAT1_LSTATUS ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  SPEED_10000 ; 
 int /*<<< orphan*/  SPEED_2500 ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int phy_read_mmd (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int aquantia_read_status(struct phy_device *phydev)
{
	int reg;

	reg = phy_read_mmd(phydev, MDIO_MMD_AN, MDIO_STAT1);
	reg = phy_read_mmd(phydev, MDIO_MMD_AN, MDIO_STAT1);
	if (reg & MDIO_STAT1_LSTATUS)
		phydev->link = 1;
	else
		phydev->link = 0;

	reg = phy_read_mmd(phydev, MDIO_MMD_AN, 0xc800);
	mdelay(10);
	reg = phy_read_mmd(phydev, MDIO_MMD_AN, 0xc800);

	switch (reg) {
	case 0x9:
		phydev->speed = SPEED_2500;
		break;
	case 0x5:
		phydev->speed = SPEED_1000;
		break;
	case 0x3:
		phydev->speed = SPEED_100;
		break;
	case 0x7:
	default:
		phydev->speed = SPEED_10000;
		break;
	}
	phydev->duplex = DUPLEX_FULL;

	return 0;
}