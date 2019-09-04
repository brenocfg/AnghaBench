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
typedef  int /*<<< orphan*/  u32 ;
struct stmmac_priv {int flow_ctrl; int /*<<< orphan*/  pause; TYPE_2__* hw; int /*<<< orphan*/  ioaddr; TYPE_1__* plat; } ;
struct rgmii_adv {int /*<<< orphan*/  pause; } ;
struct phy_device {int supported; int autoneg; int /*<<< orphan*/  duplex; } ;
struct net_device {struct phy_device* phydev; } ;
struct ethtool_pauseparam {int autoneg; scalar_t__ tx_pause; scalar_t__ rx_pause; } ;
struct TYPE_4__ {scalar_t__ pcs; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_queues_to_use; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int FLOW_OFF ; 
 int FLOW_RX ; 
 int FLOW_TX ; 
 int SUPPORTED_Asym_Pause ; 
 int SUPPORTED_Pause ; 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int phy_start_aneg (struct phy_device*) ; 
 int /*<<< orphan*/  stmmac_flow_ctrl (struct stmmac_priv*,TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stmmac_pcs_get_adv_lp (struct stmmac_priv*,int /*<<< orphan*/ ,struct rgmii_adv*) ; 

__attribute__((used)) static int
stmmac_set_pauseparam(struct net_device *netdev,
		      struct ethtool_pauseparam *pause)
{
	struct stmmac_priv *priv = netdev_priv(netdev);
	u32 tx_cnt = priv->plat->tx_queues_to_use;
	struct phy_device *phy = netdev->phydev;
	int new_pause = FLOW_OFF;
	struct rgmii_adv adv_lp;

	if (priv->hw->pcs && !stmmac_pcs_get_adv_lp(priv, priv->ioaddr, &adv_lp)) {
		pause->autoneg = 1;
		if (!adv_lp.pause)
			return -EOPNOTSUPP;
	} else {
		if (!(phy->supported & SUPPORTED_Pause) ||
		    !(phy->supported & SUPPORTED_Asym_Pause))
			return -EOPNOTSUPP;
	}

	if (pause->rx_pause)
		new_pause |= FLOW_RX;
	if (pause->tx_pause)
		new_pause |= FLOW_TX;

	priv->flow_ctrl = new_pause;
	phy->autoneg = pause->autoneg;

	if (phy->autoneg) {
		if (netif_running(netdev))
			return phy_start_aneg(phy);
	}

	stmmac_flow_ctrl(priv, priv->hw, phy->duplex, priv->flow_ctrl,
			priv->pause, tx_cnt);
	return 0;
}