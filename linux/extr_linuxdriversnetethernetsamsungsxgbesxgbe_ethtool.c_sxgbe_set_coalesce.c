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
struct sxgbe_priv_data {unsigned int rx_riwt; int /*<<< orphan*/  ioaddr; TYPE_1__* hw; int /*<<< orphan*/  use_riwt; } ;
struct net_device {int dummy; } ;
struct ethtool_coalesce {int /*<<< orphan*/  rx_coalesce_usecs; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* rx_watchdog ) (int /*<<< orphan*/ ,unsigned int) ;} ;
struct TYPE_3__ {TYPE_2__* dma; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 unsigned int SXGBE_MAX_DMA_RIWT ; 
 unsigned int SXGBE_MIN_DMA_RIWT ; 
 struct sxgbe_priv_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int sxgbe_usec2riwt (int /*<<< orphan*/ ,struct sxgbe_priv_data*) ; 

__attribute__((used)) static int sxgbe_set_coalesce(struct net_device *dev,
			      struct ethtool_coalesce *ec)
{
	struct sxgbe_priv_data *priv = netdev_priv(dev);
	unsigned int rx_riwt;

	if (!ec->rx_coalesce_usecs)
		return -EINVAL;

	rx_riwt = sxgbe_usec2riwt(ec->rx_coalesce_usecs, priv);

	if ((rx_riwt > SXGBE_MAX_DMA_RIWT) || (rx_riwt < SXGBE_MIN_DMA_RIWT))
		return -EINVAL;
	else if (!priv->use_riwt)
		return -EOPNOTSUPP;

	priv->rx_riwt = rx_riwt;
	priv->hw->dma->rx_watchdog(priv->ioaddr, priv->rx_riwt);

	return 0;
}