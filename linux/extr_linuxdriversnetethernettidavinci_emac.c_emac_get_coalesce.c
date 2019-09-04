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
struct ethtool_coalesce {int /*<<< orphan*/  rx_coalesce_usecs; } ;
struct emac_priv {int /*<<< orphan*/  coal_intvl; } ;

/* Variables and functions */
 struct emac_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int emac_get_coalesce(struct net_device *ndev,
				struct ethtool_coalesce *coal)
{
	struct emac_priv *priv = netdev_priv(ndev);

	coal->rx_coalesce_usecs = priv->coal_intvl;
	return 0;

}