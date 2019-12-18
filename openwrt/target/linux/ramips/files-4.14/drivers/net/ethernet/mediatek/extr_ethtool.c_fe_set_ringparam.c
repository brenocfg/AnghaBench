#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {TYPE_3__* netdev_ops; } ;
struct TYPE_5__ {void* rx_ring_size; } ;
struct TYPE_4__ {void* tx_ring_size; } ;
struct fe_priv {TYPE_2__ rx_ring; TYPE_1__ tx_ring; } ;
struct ethtool_ringparam {int tx_pending; int rx_pending; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* ndo_open ) (struct net_device*) ;int /*<<< orphan*/  (* ndo_stop ) (struct net_device*) ;} ;

/* Variables and functions */
 void* BIT (scalar_t__) ; 
 int EINVAL ; 
 int MAX_DMA_DESC ; 
 scalar_t__ fls (int) ; 
 struct fe_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 
 int /*<<< orphan*/  stub2 (struct net_device*) ; 

__attribute__((used)) static int fe_set_ringparam(struct net_device *dev,
			    struct ethtool_ringparam *ring)
{
	struct fe_priv *priv = netdev_priv(dev);

	if ((ring->tx_pending < 2) ||
	    (ring->rx_pending < 2) ||
	    (ring->rx_pending > MAX_DMA_DESC) ||
	    (ring->tx_pending > MAX_DMA_DESC))
		return -EINVAL;

	dev->netdev_ops->ndo_stop(dev);

	priv->tx_ring.tx_ring_size = BIT(fls(ring->tx_pending) - 1);
	priv->rx_ring.rx_ring_size = BIT(fls(ring->rx_pending) - 1);

	dev->netdev_ops->ndo_open(dev);

	return 0;
}