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
struct phy_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_MARVELL_COPPER_PAGE ; 
 int /*<<< orphan*/  MII_MARVELL_MSCR_PAGE ; 
 int genphy_soft_reset (struct phy_device*) ; 
 int marvell_of_reg_init (struct phy_device*) ; 
 int marvell_set_page (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_write (struct phy_device*,int,int) ; 

__attribute__((used)) static int m88e1149_config_init(struct phy_device *phydev)
{
	int err;

	/* Change address */
	err = marvell_set_page(phydev, MII_MARVELL_MSCR_PAGE);
	if (err < 0)
		return err;

	/* Enable 1000 Mbit */
	err = phy_write(phydev, 0x15, 0x1048);
	if (err < 0)
		return err;

	err = marvell_of_reg_init(phydev);
	if (err < 0)
		return err;

	/* Reset address */
	err = marvell_set_page(phydev, MII_MARVELL_COPPER_PAGE);
	if (err < 0)
		return err;

	return genphy_soft_reset(phydev);
}