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
struct phy_device {int advertising; } ;
struct net_device {struct phy_device* phydev; } ;
struct ethtool_pauseparam {scalar_t__ autoneg; scalar_t__ tx_pause; scalar_t__ rx_pause; } ;
struct ave_private {scalar_t__ pause_tx; scalar_t__ pause_rx; scalar_t__ pause_auto; } ;

/* Variables and functions */
 int ADVERTISED_Asym_Pause ; 
 int ADVERTISED_Pause ; 
 int EINVAL ; 
 struct ave_private* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  phy_start_aneg (struct phy_device*) ; 

__attribute__((used)) static int ave_ethtool_set_pauseparam(struct net_device *ndev,
				      struct ethtool_pauseparam *pause)
{
	struct ave_private *priv = netdev_priv(ndev);
	struct phy_device *phydev = ndev->phydev;

	if (!phydev)
		return -EINVAL;

	priv->pause_auto = pause->autoneg;
	priv->pause_rx   = pause->rx_pause;
	priv->pause_tx   = pause->tx_pause;

	phydev->advertising &= ~(ADVERTISED_Pause | ADVERTISED_Asym_Pause);
	if (pause->rx_pause)
		phydev->advertising |= ADVERTISED_Pause | ADVERTISED_Asym_Pause;
	if (pause->tx_pause)
		phydev->advertising ^= ADVERTISED_Asym_Pause;

	if (pause->autoneg) {
		if (netif_running(ndev))
			phy_start_aneg(phydev);
	}

	return 0;
}