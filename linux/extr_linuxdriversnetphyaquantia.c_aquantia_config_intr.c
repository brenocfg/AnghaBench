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
struct phy_device {scalar_t__ interrupts; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int /*<<< orphan*/  MDIO_MMD_VEND1 ; 
 scalar_t__ PHY_INTERRUPT_ENABLED ; 
 int phy_write_mmd (struct phy_device*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int aquantia_config_intr(struct phy_device *phydev)
{
	int err;

	if (phydev->interrupts == PHY_INTERRUPT_ENABLED) {
		err = phy_write_mmd(phydev, MDIO_MMD_AN, 0xd401, 1);
		if (err < 0)
			return err;

		err = phy_write_mmd(phydev, MDIO_MMD_VEND1, 0xff00, 1);
		if (err < 0)
			return err;

		err = phy_write_mmd(phydev, MDIO_MMD_VEND1, 0xff01, 0x1001);
	} else {
		err = phy_write_mmd(phydev, MDIO_MMD_AN, 0xd401, 0);
		if (err < 0)
			return err;

		err = phy_write_mmd(phydev, MDIO_MMD_VEND1, 0xff00, 0);
		if (err < 0)
			return err;

		err = phy_write_mmd(phydev, MDIO_MMD_VEND1, 0xff01, 0);
	}

	return err;
}