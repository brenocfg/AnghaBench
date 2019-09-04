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
struct net_device {int dummy; } ;
struct ethtool_pauseparam {int rx_pause; int tx_pause; int autoneg; } ;
struct ef4_nic {int wanted_fc; } ;

/* Variables and functions */
 int EF4_FC_AUTO ; 
 int EF4_FC_RX ; 
 int EF4_FC_TX ; 
 struct ef4_nic* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ef4_ethtool_get_pauseparam(struct net_device *net_dev,
				       struct ethtool_pauseparam *pause)
{
	struct ef4_nic *efx = netdev_priv(net_dev);

	pause->rx_pause = !!(efx->wanted_fc & EF4_FC_RX);
	pause->tx_pause = !!(efx->wanted_fc & EF4_FC_TX);
	pause->autoneg = !!(efx->wanted_fc & EF4_FC_AUTO);
}