#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct net_device {TYPE_5__* netdev_ops; } ;
struct mtk_mac {TYPE_4__* hw; } ;
struct ethtool_ringparam {int tx_pending; int rx_pending; } ;
struct TYPE_10__ {int (* ndo_open ) (struct net_device*) ;int /*<<< orphan*/  (* ndo_stop ) (struct net_device*) ;} ;
struct TYPE_7__ {void* tx_ring_size; } ;
struct TYPE_9__ {TYPE_3__* rx_ring; TYPE_2__ tx_ring; TYPE_1__* soc; } ;
struct TYPE_8__ {void* rx_ring_size; } ;
struct TYPE_6__ {scalar_t__ dma_ring_size; } ;

/* Variables and functions */
 void* BIT (scalar_t__) ; 
 int EINVAL ; 
 scalar_t__ fls (scalar_t__) ; 
 struct mtk_mac* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 
 int stub2 (struct net_device*) ; 

__attribute__((used)) static int mtk_set_ringparam(struct net_device *dev,
			     struct ethtool_ringparam *ring)
{
	struct mtk_mac *mac = netdev_priv(dev);

	if ((ring->tx_pending < 2) ||
	    (ring->rx_pending < 2) ||
	    (ring->rx_pending > mac->hw->soc->dma_ring_size) ||
	    (ring->tx_pending > mac->hw->soc->dma_ring_size))
		return -EINVAL;

	dev->netdev_ops->ndo_stop(dev);

	mac->hw->tx_ring.tx_ring_size = BIT(fls(ring->tx_pending) - 1);
	mac->hw->rx_ring[0].rx_ring_size = BIT(fls(ring->rx_pending) - 1);

	return dev->netdev_ops->ndo_open(dev);
}