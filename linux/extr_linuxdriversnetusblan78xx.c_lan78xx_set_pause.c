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
struct phy_device {int dummy; } ;
struct net_device {struct phy_device* phydev; } ;
struct lan78xx_net {scalar_t__ fc_autoneg; int /*<<< orphan*/  fc_request_control; } ;
struct ethtool_pauseparam {scalar_t__ autoneg; scalar_t__ tx_pause; scalar_t__ rx_pause; } ;
struct TYPE_4__ {int /*<<< orphan*/  advertising; } ;
struct TYPE_3__ {scalar_t__ autoneg; } ;
struct ethtool_link_ksettings {TYPE_2__ link_modes; TYPE_1__ base; } ;

/* Variables and functions */
 int ADVERTISED_Asym_Pause ; 
 int ADVERTISED_Pause ; 
 int EINVAL ; 
 int /*<<< orphan*/  FLOW_CTRL_RX ; 
 int /*<<< orphan*/  FLOW_CTRL_TX ; 
 int /*<<< orphan*/  ethtool_convert_legacy_u32_to_link_mode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ethtool_convert_link_mode_to_legacy_u32 (int*,int /*<<< orphan*/ ) ; 
 int mii_adv_to_ethtool_adv_t (int) ; 
 scalar_t__ mii_advertise_flowctrl (int /*<<< orphan*/ ) ; 
 struct lan78xx_net* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_ethtool_ksettings_get (struct phy_device*,struct ethtool_link_ksettings*) ; 
 int /*<<< orphan*/  phy_ethtool_ksettings_set (struct phy_device*,struct ethtool_link_ksettings*) ; 

__attribute__((used)) static int lan78xx_set_pause(struct net_device *net,
			     struct ethtool_pauseparam *pause)
{
	struct lan78xx_net *dev = netdev_priv(net);
	struct phy_device *phydev = net->phydev;
	struct ethtool_link_ksettings ecmd;
	int ret;

	phy_ethtool_ksettings_get(phydev, &ecmd);

	if (pause->autoneg && !ecmd.base.autoneg) {
		ret = -EINVAL;
		goto exit;
	}

	dev->fc_request_control = 0;
	if (pause->rx_pause)
		dev->fc_request_control |= FLOW_CTRL_RX;

	if (pause->tx_pause)
		dev->fc_request_control |= FLOW_CTRL_TX;

	if (ecmd.base.autoneg) {
		u32 mii_adv;
		u32 advertising;

		ethtool_convert_link_mode_to_legacy_u32(
			&advertising, ecmd.link_modes.advertising);

		advertising &= ~(ADVERTISED_Pause | ADVERTISED_Asym_Pause);
		mii_adv = (u32)mii_advertise_flowctrl(dev->fc_request_control);
		advertising |= mii_adv_to_ethtool_adv_t(mii_adv);

		ethtool_convert_legacy_u32_to_link_mode(
			ecmd.link_modes.advertising, advertising);

		phy_ethtool_ksettings_set(phydev, &ecmd);
	}

	dev->fc_autoneg = pause->autoneg;

	ret = 0;
exit:
	return ret;
}