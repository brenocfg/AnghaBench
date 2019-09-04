#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct net_device {int dummy; } ;
struct mii_if_info {int (* mdio_read ) (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int full_duplex; scalar_t__ supports_gmii; int /*<<< orphan*/  phy_id; struct net_device* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  lp_advertising; int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct TYPE_3__ {int duplex; void* speed; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  mdio_support; int /*<<< orphan*/  phy_address; int /*<<< orphan*/  port; } ;
struct ethtool_link_ksettings {TYPE_2__ link_modes; TYPE_1__ base; } ;

/* Variables and functions */
 int ADVERTISED_1000baseT_Full ; 
 int ADVERTISED_1000baseT_Half ; 
 int ADVERTISED_100baseT_Full ; 
 int ADVERTISED_100baseT_Half ; 
 int ADVERTISED_10baseT_Full ; 
 int ADVERTISED_Autoneg ; 
 int ADVERTISED_MII ; 
 int ADVERTISED_TP ; 
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int BMCR_ANENABLE ; 
 int BMCR_FULLDPLX ; 
 int BMCR_SPEED100 ; 
 int BMCR_SPEED1000 ; 
 int BMSR_ANEGCOMPLETE ; 
 int DUPLEX_FULL ; 
 int DUPLEX_HALF ; 
 int /*<<< orphan*/  ETH_MDIO_SUPPORTS_C22 ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int /*<<< orphan*/  MII_CTRL1000 ; 
 int /*<<< orphan*/  MII_LPA ; 
 int /*<<< orphan*/  MII_STAT1000 ; 
 int /*<<< orphan*/  PORT_MII ; 
 void* SPEED_10 ; 
 void* SPEED_100 ; 
 void* SPEED_1000 ; 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_1000baseT_Half ; 
 int SUPPORTED_100baseT_Full ; 
 int SUPPORTED_100baseT_Half ; 
 int SUPPORTED_10baseT_Full ; 
 int SUPPORTED_10baseT_Half ; 
 int SUPPORTED_Autoneg ; 
 int SUPPORTED_MII ; 
 int SUPPORTED_TP ; 
 int /*<<< orphan*/  ethtool_convert_legacy_u32_to_link_mode (int /*<<< orphan*/ ,int) ; 
 int mii_ctrl1000_to_ethtool_adv_t (int) ; 
 int mii_get_an (struct mii_if_info*,int /*<<< orphan*/ ) ; 
 int mii_stat1000_to_ethtool_lpa_t (int) ; 
 int stub1 (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub3 (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub4 (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mii_ethtool_get_link_ksettings(struct mii_if_info *mii,
				    struct ethtool_link_ksettings *cmd)
{
	struct net_device *dev = mii->dev;
	u16 bmcr, bmsr, ctrl1000 = 0, stat1000 = 0;
	u32 nego, supported, advertising, lp_advertising;

	supported = (SUPPORTED_10baseT_Half | SUPPORTED_10baseT_Full |
		     SUPPORTED_100baseT_Half | SUPPORTED_100baseT_Full |
		     SUPPORTED_Autoneg | SUPPORTED_TP | SUPPORTED_MII);
	if (mii->supports_gmii)
		supported |= SUPPORTED_1000baseT_Half |
			SUPPORTED_1000baseT_Full;

	/* only supports twisted-pair */
	cmd->base.port = PORT_MII;

	/* this isn't fully supported at higher layers */
	cmd->base.phy_address = mii->phy_id;
	cmd->base.mdio_support = ETH_MDIO_SUPPORTS_C22;

	advertising = ADVERTISED_TP | ADVERTISED_MII;

	bmcr = mii->mdio_read(dev, mii->phy_id, MII_BMCR);
	bmsr = mii->mdio_read(dev, mii->phy_id, MII_BMSR);
	if (mii->supports_gmii) {
		ctrl1000 = mii->mdio_read(dev, mii->phy_id, MII_CTRL1000);
		stat1000 = mii->mdio_read(dev, mii->phy_id, MII_STAT1000);
	}
	if (bmcr & BMCR_ANENABLE) {
		advertising |= ADVERTISED_Autoneg;
		cmd->base.autoneg = AUTONEG_ENABLE;

		advertising |= mii_get_an(mii, MII_ADVERTISE);
		if (mii->supports_gmii)
			advertising |= mii_ctrl1000_to_ethtool_adv_t(ctrl1000);

		if (bmsr & BMSR_ANEGCOMPLETE) {
			lp_advertising = mii_get_an(mii, MII_LPA);
			lp_advertising |=
					mii_stat1000_to_ethtool_lpa_t(stat1000);
		} else {
			lp_advertising = 0;
		}

		nego = advertising & lp_advertising;

		if (nego & (ADVERTISED_1000baseT_Full |
			    ADVERTISED_1000baseT_Half)) {
			cmd->base.speed = SPEED_1000;
			cmd->base.duplex = !!(nego & ADVERTISED_1000baseT_Full);
		} else if (nego & (ADVERTISED_100baseT_Full |
				   ADVERTISED_100baseT_Half)) {
			cmd->base.speed = SPEED_100;
			cmd->base.duplex = !!(nego & ADVERTISED_100baseT_Full);
		} else {
			cmd->base.speed = SPEED_10;
			cmd->base.duplex = !!(nego & ADVERTISED_10baseT_Full);
		}
	} else {
		cmd->base.autoneg = AUTONEG_DISABLE;

		cmd->base.speed = ((bmcr & BMCR_SPEED1000 &&
				    (bmcr & BMCR_SPEED100) == 0) ?
				   SPEED_1000 :
				   ((bmcr & BMCR_SPEED100) ?
				    SPEED_100 : SPEED_10));
		cmd->base.duplex = (bmcr & BMCR_FULLDPLX) ?
			DUPLEX_FULL : DUPLEX_HALF;

		lp_advertising = 0;
	}

	mii->full_duplex = cmd->base.duplex;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.lp_advertising,
						lp_advertising);

	/* ignore maxtxpkt, maxrxpkt for now */
}