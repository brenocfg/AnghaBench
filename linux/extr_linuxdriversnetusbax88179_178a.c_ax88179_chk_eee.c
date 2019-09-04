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
struct usbnet {int /*<<< orphan*/  mii; scalar_t__ data; } ;
struct ethtool_cmd {int duplex; scalar_t__ speed; int /*<<< orphan*/  cmd; } ;
struct ax88179_data {int eee_active; } ;

/* Variables and functions */
 int DUPLEX_FULL ; 
 int /*<<< orphan*/  ETHTOOL_GSET ; 
 int /*<<< orphan*/  MDIO_AN_EEE_ADV ; 
 int /*<<< orphan*/  MDIO_AN_EEE_LPABLE ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int /*<<< orphan*/  MDIO_MMD_PCS ; 
 int /*<<< orphan*/  MDIO_PCS_EEE_ABLE ; 
 scalar_t__ SPEED_1000 ; 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_100baseT_Full ; 
 int ax88179_phy_read_mmd_indirect (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_ethtool_gset (int /*<<< orphan*/ *,struct ethtool_cmd*) ; 
 int mmd_eee_adv_to_ethtool_adv_t (int) ; 
 int mmd_eee_cap_to_ethtool_sup_t (int) ; 

__attribute__((used)) static int ax88179_chk_eee(struct usbnet *dev)
{
	struct ethtool_cmd ecmd = { .cmd = ETHTOOL_GSET };
	struct ax88179_data *priv = (struct ax88179_data *)dev->data;

	mii_ethtool_gset(&dev->mii, &ecmd);

	if (ecmd.duplex & DUPLEX_FULL) {
		int eee_lp, eee_cap, eee_adv;
		u32 lp, cap, adv, supported = 0;

		eee_cap = ax88179_phy_read_mmd_indirect(dev,
							MDIO_PCS_EEE_ABLE,
							MDIO_MMD_PCS);
		if (eee_cap < 0) {
			priv->eee_active = 0;
			return false;
		}

		cap = mmd_eee_cap_to_ethtool_sup_t(eee_cap);
		if (!cap) {
			priv->eee_active = 0;
			return false;
		}

		eee_lp = ax88179_phy_read_mmd_indirect(dev,
						       MDIO_AN_EEE_LPABLE,
						       MDIO_MMD_AN);
		if (eee_lp < 0) {
			priv->eee_active = 0;
			return false;
		}

		eee_adv = ax88179_phy_read_mmd_indirect(dev,
							MDIO_AN_EEE_ADV,
							MDIO_MMD_AN);

		if (eee_adv < 0) {
			priv->eee_active = 0;
			return false;
		}

		adv = mmd_eee_adv_to_ethtool_adv_t(eee_adv);
		lp = mmd_eee_adv_to_ethtool_adv_t(eee_lp);
		supported = (ecmd.speed == SPEED_1000) ?
			     SUPPORTED_1000baseT_Full :
			     SUPPORTED_100baseT_Full;

		if (!(lp & adv & supported)) {
			priv->eee_active = 0;
			return false;
		}

		priv->eee_active = 1;
		return true;
	}

	priv->eee_active = 0;
	return false;
}