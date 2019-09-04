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
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct mii_if_info {scalar_t__ (* mdio_read ) (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int force_media; int full_duplex; int /*<<< orphan*/  phy_id; int /*<<< orphan*/  (* mdio_write ) (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ;scalar_t__ supports_gmii; scalar_t__ advertising; struct net_device* dev; } ;
struct TYPE_4__ {scalar_t__ speed; scalar_t__ duplex; scalar_t__ port; scalar_t__ autoneg; int /*<<< orphan*/  phy_address; } ;
struct TYPE_3__ {int /*<<< orphan*/  advertising; } ;
struct ethtool_link_ksettings {TYPE_2__ base; TYPE_1__ link_modes; } ;

/* Variables and functions */
 scalar_t__ ADVERTISED_1000baseT_Full ; 
 scalar_t__ ADVERTISED_1000baseT_Half ; 
 scalar_t__ ADVERTISED_100baseT_Full ; 
 scalar_t__ ADVERTISED_100baseT_Half ; 
 scalar_t__ ADVERTISED_10baseT_Full ; 
 scalar_t__ ADVERTISED_10baseT_Half ; 
 scalar_t__ ADVERTISE_1000FULL ; 
 scalar_t__ ADVERTISE_1000HALF ; 
 scalar_t__ ADVERTISE_100BASE4 ; 
 scalar_t__ ADVERTISE_ALL ; 
 scalar_t__ AUTONEG_DISABLE ; 
 scalar_t__ AUTONEG_ENABLE ; 
 scalar_t__ BMCR_ANENABLE ; 
 scalar_t__ BMCR_ANRESTART ; 
 scalar_t__ BMCR_FULLDPLX ; 
 scalar_t__ BMCR_SPEED100 ; 
 scalar_t__ BMCR_SPEED1000 ; 
 scalar_t__ DUPLEX_FULL ; 
 scalar_t__ DUPLEX_HALF ; 
 int EINVAL ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_CTRL1000 ; 
 scalar_t__ PORT_MII ; 
 scalar_t__ SPEED_10 ; 
 scalar_t__ SPEED_100 ; 
 scalar_t__ SPEED_1000 ; 
 scalar_t__ ethtool_adv_to_mii_adv_t (scalar_t__) ; 
 scalar_t__ ethtool_adv_to_mii_ctrl1000_t (scalar_t__) ; 
 int /*<<< orphan*/  ethtool_convert_link_mode_to_legacy_u32 (scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub4 (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ stub5 (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ stub7 (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int mii_ethtool_set_link_ksettings(struct mii_if_info *mii,
				   const struct ethtool_link_ksettings *cmd)
{
	struct net_device *dev = mii->dev;
	u32 speed = cmd->base.speed;

	if (speed != SPEED_10 &&
	    speed != SPEED_100 &&
	    speed != SPEED_1000)
		return -EINVAL;
	if (cmd->base.duplex != DUPLEX_HALF && cmd->base.duplex != DUPLEX_FULL)
		return -EINVAL;
	if (cmd->base.port != PORT_MII)
		return -EINVAL;
	if (cmd->base.phy_address != mii->phy_id)
		return -EINVAL;
	if (cmd->base.autoneg != AUTONEG_DISABLE &&
	    cmd->base.autoneg != AUTONEG_ENABLE)
		return -EINVAL;
	if ((speed == SPEED_1000) && (!mii->supports_gmii))
		return -EINVAL;

	/* ignore supported, maxtxpkt, maxrxpkt */

	if (cmd->base.autoneg == AUTONEG_ENABLE) {
		u32 bmcr, advert, tmp;
		u32 advert2 = 0, tmp2 = 0;
		u32 advertising;

		ethtool_convert_link_mode_to_legacy_u32(
			&advertising, cmd->link_modes.advertising);

		if ((advertising & (ADVERTISED_10baseT_Half |
				    ADVERTISED_10baseT_Full |
				    ADVERTISED_100baseT_Half |
				    ADVERTISED_100baseT_Full |
				    ADVERTISED_1000baseT_Half |
				    ADVERTISED_1000baseT_Full)) == 0)
			return -EINVAL;

		/* advertise only what has been requested */
		advert = mii->mdio_read(dev, mii->phy_id, MII_ADVERTISE);
		tmp = advert & ~(ADVERTISE_ALL | ADVERTISE_100BASE4);
		if (mii->supports_gmii) {
			advert2 = mii->mdio_read(dev, mii->phy_id,
						 MII_CTRL1000);
			tmp2 = advert2 &
				~(ADVERTISE_1000HALF | ADVERTISE_1000FULL);
		}
		tmp |= ethtool_adv_to_mii_adv_t(advertising);

		if (mii->supports_gmii)
			tmp2 |= ethtool_adv_to_mii_ctrl1000_t(advertising);
		if (advert != tmp) {
			mii->mdio_write(dev, mii->phy_id, MII_ADVERTISE, tmp);
			mii->advertising = tmp;
		}
		if ((mii->supports_gmii) && (advert2 != tmp2))
			mii->mdio_write(dev, mii->phy_id, MII_CTRL1000, tmp2);

		/* turn on autonegotiation, and force a renegotiate */
		bmcr = mii->mdio_read(dev, mii->phy_id, MII_BMCR);
		bmcr |= (BMCR_ANENABLE | BMCR_ANRESTART);
		mii->mdio_write(dev, mii->phy_id, MII_BMCR, bmcr);

		mii->force_media = 0;
	} else {
		u32 bmcr, tmp;

		/* turn off auto negotiation, set speed and duplexity */
		bmcr = mii->mdio_read(dev, mii->phy_id, MII_BMCR);
		tmp = bmcr & ~(BMCR_ANENABLE | BMCR_SPEED100 |
			       BMCR_SPEED1000 | BMCR_FULLDPLX);
		if (speed == SPEED_1000)
			tmp |= BMCR_SPEED1000;
		else if (speed == SPEED_100)
			tmp |= BMCR_SPEED100;
		if (cmd->base.duplex == DUPLEX_FULL) {
			tmp |= BMCR_FULLDPLX;
			mii->full_duplex = 1;
		} else {
			mii->full_duplex = 0;
		}
		if (bmcr != tmp)
			mii->mdio_write(dev, mii->phy_id, MII_BMCR, tmp);

		mii->force_media = 1;
	}
	return 0;
}