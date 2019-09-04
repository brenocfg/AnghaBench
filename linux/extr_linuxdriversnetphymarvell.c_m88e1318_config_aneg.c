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
 int /*<<< orphan*/  MII_88E1318S_PHY_MSCR1_PAD_ODD ; 
 int /*<<< orphan*/  MII_88E1318S_PHY_MSCR1_REG ; 
 int /*<<< orphan*/  MII_MARVELL_MSCR_PAGE ; 
 int m88e1121_config_aneg (struct phy_device*) ; 
 int phy_modify_paged (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int m88e1318_config_aneg(struct phy_device *phydev)
{
	int err;

	err = phy_modify_paged(phydev, MII_MARVELL_MSCR_PAGE,
			       MII_88E1318S_PHY_MSCR1_REG,
			       0, MII_88E1318S_PHY_MSCR1_PAD_ODD);
	if (err < 0)
		return err;

	return m88e1121_config_aneg(phydev);
}