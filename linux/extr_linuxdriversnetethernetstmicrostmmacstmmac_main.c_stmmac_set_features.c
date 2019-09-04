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
struct stmmac_priv {TYPE_2__* hw; TYPE_1__* plat; } ;
struct net_device {int dummy; } ;
typedef  int netdev_features_t ;
struct TYPE_4__ {scalar_t__ rx_csum; } ;
struct TYPE_3__ {scalar_t__ rx_coe; } ;

/* Variables and functions */
 int NETIF_F_RXCSUM ; 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stmmac_rx_ipc (struct stmmac_priv*,TYPE_2__*) ; 

__attribute__((used)) static int stmmac_set_features(struct net_device *netdev,
			       netdev_features_t features)
{
	struct stmmac_priv *priv = netdev_priv(netdev);

	/* Keep the COE Type in case of csum is supporting */
	if (features & NETIF_F_RXCSUM)
		priv->hw->rx_csum = priv->plat->rx_coe;
	else
		priv->hw->rx_csum = 0;
	/* No check needed because rx_coe has been set before and it will be
	 * fixed in case of issue.
	 */
	stmmac_rx_ipc(priv, priv->hw);

	return 0;
}