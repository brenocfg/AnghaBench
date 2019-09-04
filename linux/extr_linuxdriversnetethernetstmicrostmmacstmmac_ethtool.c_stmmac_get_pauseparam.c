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
struct stmmac_priv {int flow_ctrl; int /*<<< orphan*/  ioaddr; TYPE_1__* hw; } ;
struct rgmii_adv {int /*<<< orphan*/  pause; } ;
struct net_device {TYPE_2__* phydev; } ;
struct ethtool_pauseparam {int rx_pause; int tx_pause; int autoneg; } ;
struct TYPE_4__ {int supported; int autoneg; } ;
struct TYPE_3__ {scalar_t__ pcs; } ;

/* Variables and functions */
 int FLOW_RX ; 
 int FLOW_TX ; 
 int SUPPORTED_Asym_Pause ; 
 int SUPPORTED_Pause ; 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stmmac_pcs_get_adv_lp (struct stmmac_priv*,int /*<<< orphan*/ ,struct rgmii_adv*) ; 

__attribute__((used)) static void
stmmac_get_pauseparam(struct net_device *netdev,
		      struct ethtool_pauseparam *pause)
{
	struct stmmac_priv *priv = netdev_priv(netdev);
	struct rgmii_adv adv_lp;

	pause->rx_pause = 0;
	pause->tx_pause = 0;

	if (priv->hw->pcs && !stmmac_pcs_get_adv_lp(priv, priv->ioaddr, &adv_lp)) {
		pause->autoneg = 1;
		if (!adv_lp.pause)
			return;
	} else {
		if (!(netdev->phydev->supported & SUPPORTED_Pause) ||
		    !(netdev->phydev->supported & SUPPORTED_Asym_Pause))
			return;
	}

	pause->autoneg = netdev->phydev->autoneg;

	if (priv->flow_ctrl & FLOW_RX)
		pause->rx_pause = 1;
	if (priv->flow_ctrl & FLOW_TX)
		pause->tx_pause = 1;

}