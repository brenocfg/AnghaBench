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
struct phy_device {scalar_t__ autoneg; scalar_t__ speed; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int /*<<< orphan*/  MII_VSC82X4_EXT_PAGE_16E ; 
 int /*<<< orphan*/  MII_VSC82X4_EXT_PAGE_17E ; 
 int /*<<< orphan*/  MII_VSC82X4_EXT_PAGE_18E ; 
 int /*<<< orphan*/  MII_VSC82X4_EXT_PAGE_ACCESS ; 
 scalar_t__ SPEED_100 ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vsc82x4_config_autocross_enable(struct phy_device *phydev)
{
	int ret;

	if (phydev->autoneg == AUTONEG_ENABLE || phydev->speed > SPEED_100)
		return 0;

	/* map extended registers set 0x10 - 0x1e */
	ret = phy_write(phydev, MII_VSC82X4_EXT_PAGE_ACCESS, 0x52b5);
	if (ret >= 0)
		ret = phy_write(phydev, MII_VSC82X4_EXT_PAGE_18E, 0x0012);
	if (ret >= 0)
		ret = phy_write(phydev, MII_VSC82X4_EXT_PAGE_17E, 0x2803);
	if (ret >= 0)
		ret = phy_write(phydev, MII_VSC82X4_EXT_PAGE_16E, 0x87fa);
	/* map standard registers set 0x10 - 0x1e */
	if (ret >= 0)
		ret = phy_write(phydev, MII_VSC82X4_EXT_PAGE_ACCESS, 0x0000);
	else
		phy_write(phydev, MII_VSC82X4_EXT_PAGE_ACCESS, 0x0000);

	return ret;
}