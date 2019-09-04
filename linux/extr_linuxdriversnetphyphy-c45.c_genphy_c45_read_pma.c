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
struct phy_device {int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  MDIO_CTRL1 ; 
#define  MDIO_CTRL1_SPEED10G 130 
 int MDIO_CTRL1_SPEEDSEL ; 
 int /*<<< orphan*/  MDIO_MMD_PMAPMD ; 
#define  MDIO_PMA_CTRL1_SPEED100 129 
#define  MDIO_PMA_CTRL1_SPEED1000 128 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  SPEED_10000 ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 
 int phy_read_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int genphy_c45_read_pma(struct phy_device *phydev)
{
	int val;

	val = phy_read_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_CTRL1);
	if (val < 0)
		return val;

	switch (val & MDIO_CTRL1_SPEEDSEL) {
	case 0:
		phydev->speed = SPEED_10;
		break;
	case MDIO_PMA_CTRL1_SPEED100:
		phydev->speed = SPEED_100;
		break;
	case MDIO_PMA_CTRL1_SPEED1000:
		phydev->speed = SPEED_1000;
		break;
	case MDIO_CTRL1_SPEED10G:
		phydev->speed = SPEED_10000;
		break;
	default:
		phydev->speed = SPEED_UNKNOWN;
		break;
	}

	phydev->duplex = DUPLEX_FULL;

	return 0;
}