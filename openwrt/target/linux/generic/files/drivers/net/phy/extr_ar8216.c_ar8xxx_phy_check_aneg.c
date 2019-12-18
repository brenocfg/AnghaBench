#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct phy_device {scalar_t__ autoneg; TYPE_1__ mdio; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int BMCR_ANENABLE ; 
 int BMCR_ANRESTART ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ar8xxx_phy_check_aneg(struct phy_device *phydev)
{
	int ret;

	if (phydev->autoneg != AUTONEG_ENABLE)
		return 0;
	/*
	 * BMCR_ANENABLE might have been cleared
	 * by phy_init_hw in certain kernel versions
	 * therefore check for it
	 */
	ret = phy_read(phydev, MII_BMCR);
	if (ret < 0)
		return ret;
	if (ret & BMCR_ANENABLE)
		return 0;

	dev_info(&phydev->mdio.dev, "ANEG disabled, re-enabling ...\n");
	ret |= BMCR_ANENABLE | BMCR_ANRESTART;
	return phy_write(phydev, MII_BMCR, ret);
}