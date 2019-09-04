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
struct phy_device {int pause; int asym_pause; int /*<<< orphan*/  lp_advertising; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVERTISED_10000baseT_Full ; 
 int LPA_PAUSE_ASYM ; 
 int LPA_PAUSE_CAP ; 
 int /*<<< orphan*/  MDIO_AN_10GBT_STAT ; 
 int MDIO_AN_10GBT_STAT_LP10G ; 
 int /*<<< orphan*/  MDIO_AN_LPA ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int /*<<< orphan*/  mii_lpa_to_ethtool_lpa_t (int) ; 
 int phy_read_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int genphy_c45_read_lpa(struct phy_device *phydev)
{
	int val;

	/* Read the link partner's base page advertisement */
	val = phy_read_mmd(phydev, MDIO_MMD_AN, MDIO_AN_LPA);
	if (val < 0)
		return val;

	phydev->lp_advertising = mii_lpa_to_ethtool_lpa_t(val);
	phydev->pause = val & LPA_PAUSE_CAP ? 1 : 0;
	phydev->asym_pause = val & LPA_PAUSE_ASYM ? 1 : 0;

	/* Read the link partner's 10G advertisement */
	val = phy_read_mmd(phydev, MDIO_MMD_AN, MDIO_AN_10GBT_STAT);
	if (val < 0)
		return val;

	if (val & MDIO_AN_10GBT_STAT_LP10G)
		phydev->lp_advertising |= ADVERTISED_10000baseT_Full;

	return 0;
}