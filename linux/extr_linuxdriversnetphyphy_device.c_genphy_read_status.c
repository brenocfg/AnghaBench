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
struct phy_device {scalar_t__ autoneg; int supported; scalar_t__ duplex; int pause; int asym_pause; void* speed; int /*<<< orphan*/  lp_advertising; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int BMCR_FULLDPLX ; 
 int BMCR_SPEED100 ; 
 int BMCR_SPEED1000 ; 
 int CTL1000_ENABLE_MASTER ; 
 scalar_t__ DUPLEX_FULL ; 
 void* DUPLEX_HALF ; 
 int ENOLINK ; 
 int LPA_1000FULL ; 
 int LPA_1000HALF ; 
 int LPA_1000MSFAIL ; 
 int LPA_100FULL ; 
 int LPA_100HALF ; 
 int LPA_10FULL ; 
 int LPA_PAUSE_ASYM ; 
 int LPA_PAUSE_CAP ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_CTRL1000 ; 
 int /*<<< orphan*/  MII_LPA ; 
 int /*<<< orphan*/  MII_STAT1000 ; 
 void* SPEED_10 ; 
 void* SPEED_100 ; 
 void* SPEED_1000 ; 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_1000baseT_Half ; 
 int genphy_update_link (struct phy_device*) ; 
 int /*<<< orphan*/  mii_lpa_to_ethtool_lpa_t (int) ; 
 int /*<<< orphan*/  mii_stat1000_to_ethtool_lpa_t (int) ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phydev_err (struct phy_device*,char*) ; 

int genphy_read_status(struct phy_device *phydev)
{
	int adv;
	int err;
	int lpa;
	int lpagb = 0;
	int common_adv;
	int common_adv_gb = 0;

	/* Update the link, but return if there was an error */
	err = genphy_update_link(phydev);
	if (err)
		return err;

	phydev->lp_advertising = 0;

	if (AUTONEG_ENABLE == phydev->autoneg) {
		if (phydev->supported & (SUPPORTED_1000baseT_Half
					| SUPPORTED_1000baseT_Full)) {
			lpagb = phy_read(phydev, MII_STAT1000);
			if (lpagb < 0)
				return lpagb;

			adv = phy_read(phydev, MII_CTRL1000);
			if (adv < 0)
				return adv;

			if (lpagb & LPA_1000MSFAIL) {
				if (adv & CTL1000_ENABLE_MASTER)
					phydev_err(phydev, "Master/Slave resolution failed, maybe conflicting manual settings?\n");
				else
					phydev_err(phydev, "Master/Slave resolution failed\n");
				return -ENOLINK;
			}

			phydev->lp_advertising =
				mii_stat1000_to_ethtool_lpa_t(lpagb);
			common_adv_gb = lpagb & adv << 2;
		}

		lpa = phy_read(phydev, MII_LPA);
		if (lpa < 0)
			return lpa;

		phydev->lp_advertising |= mii_lpa_to_ethtool_lpa_t(lpa);

		adv = phy_read(phydev, MII_ADVERTISE);
		if (adv < 0)
			return adv;

		common_adv = lpa & adv;

		phydev->speed = SPEED_10;
		phydev->duplex = DUPLEX_HALF;
		phydev->pause = 0;
		phydev->asym_pause = 0;

		if (common_adv_gb & (LPA_1000FULL | LPA_1000HALF)) {
			phydev->speed = SPEED_1000;

			if (common_adv_gb & LPA_1000FULL)
				phydev->duplex = DUPLEX_FULL;
		} else if (common_adv & (LPA_100FULL | LPA_100HALF)) {
			phydev->speed = SPEED_100;

			if (common_adv & LPA_100FULL)
				phydev->duplex = DUPLEX_FULL;
		} else
			if (common_adv & LPA_10FULL)
				phydev->duplex = DUPLEX_FULL;

		if (phydev->duplex == DUPLEX_FULL) {
			phydev->pause = lpa & LPA_PAUSE_CAP ? 1 : 0;
			phydev->asym_pause = lpa & LPA_PAUSE_ASYM ? 1 : 0;
		}
	} else {
		int bmcr = phy_read(phydev, MII_BMCR);

		if (bmcr < 0)
			return bmcr;

		if (bmcr & BMCR_FULLDPLX)
			phydev->duplex = DUPLEX_FULL;
		else
			phydev->duplex = DUPLEX_HALF;

		if (bmcr & BMCR_SPEED1000)
			phydev->speed = SPEED_1000;
		else if (bmcr & BMCR_SPEED100)
			phydev->speed = SPEED_100;
		else
			phydev->speed = SPEED_10;

		phydev->pause = 0;
		phydev->asym_pause = 0;
	}

	return 0;
}