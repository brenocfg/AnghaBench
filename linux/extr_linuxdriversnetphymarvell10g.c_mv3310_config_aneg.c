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
typedef  int u32 ;
struct phy_device {scalar_t__ autoneg; int advertising; int supported; int /*<<< orphan*/  mdix_ctrl; } ;

/* Variables and functions */
 int ADVERTISED_10000baseT_Full ; 
 int ADVERTISE_1000FULL ; 
 int ADVERTISE_1000HALF ; 
 int ADVERTISE_100BASE4 ; 
 int ADVERTISE_ALL ; 
 int ADVERTISE_PAUSE_ASYM ; 
 int ADVERTISE_PAUSE_CAP ; 
 scalar_t__ AUTONEG_DISABLE ; 
 int /*<<< orphan*/  ETH_TP_MDI_AUTO ; 
 int /*<<< orphan*/  MDIO_AN_10GBT_CTRL ; 
 int MDIO_AN_10GBT_CTRL_ADV10G ; 
 int /*<<< orphan*/  MDIO_AN_ADVERTISE ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int /*<<< orphan*/  MV_AN_CTRL1000 ; 
 int ethtool_adv_to_mii_adv_t (int) ; 
 int ethtool_adv_to_mii_ctrl1000_t (int) ; 
 int genphy_c45_an_disable_aneg (struct phy_device*) ; 
 int genphy_c45_pma_setup_forced (struct phy_device*) ; 
 int genphy_c45_restart_aneg (struct phy_device*) ; 
 int mv3310_modify (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int mv3310_config_aneg(struct phy_device *phydev)
{
	bool changed = false;
	u32 advertising;
	int ret;

	/* We don't support manual MDI control */
	phydev->mdix_ctrl = ETH_TP_MDI_AUTO;

	if (phydev->autoneg == AUTONEG_DISABLE) {
		ret = genphy_c45_pma_setup_forced(phydev);
		if (ret < 0)
			return ret;

		return genphy_c45_an_disable_aneg(phydev);
	}

	phydev->advertising &= phydev->supported;
	advertising = phydev->advertising;

	ret = mv3310_modify(phydev, MDIO_MMD_AN, MDIO_AN_ADVERTISE,
			    ADVERTISE_ALL | ADVERTISE_100BASE4 |
			    ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM,
			    ethtool_adv_to_mii_adv_t(advertising));
	if (ret < 0)
		return ret;
	if (ret > 0)
		changed = true;

	ret = mv3310_modify(phydev, MDIO_MMD_AN, MV_AN_CTRL1000,
			    ADVERTISE_1000FULL | ADVERTISE_1000HALF,
			    ethtool_adv_to_mii_ctrl1000_t(advertising));
	if (ret < 0)
		return ret;
	if (ret > 0)
		changed = true;

	/* 10G control register */
	ret = mv3310_modify(phydev, MDIO_MMD_AN, MDIO_AN_10GBT_CTRL,
			    MDIO_AN_10GBT_CTRL_ADV10G,
			    advertising & ADVERTISED_10000baseT_Full ?
				MDIO_AN_10GBT_CTRL_ADV10G : 0);
	if (ret < 0)
		return ret;
	if (ret > 0)
		changed = true;

	if (changed)
		ret = genphy_c45_restart_aneg(phydev);

	return ret;
}