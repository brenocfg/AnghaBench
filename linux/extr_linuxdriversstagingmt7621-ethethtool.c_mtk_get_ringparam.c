#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct mtk_mac {TYPE_4__* hw; } ;
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  tx_max_pending; int /*<<< orphan*/  rx_max_pending; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx_ring_size; } ;
struct TYPE_8__ {TYPE_2__ tx_ring; TYPE_1__* rx_ring; TYPE_3__* soc; } ;
struct TYPE_7__ {int /*<<< orphan*/  dma_ring_size; } ;
struct TYPE_5__ {int /*<<< orphan*/  rx_ring_size; } ;

/* Variables and functions */
 struct mtk_mac* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void mtk_get_ringparam(struct net_device *dev,
			      struct ethtool_ringparam *ring)
{
	struct mtk_mac *mac = netdev_priv(dev);

	ring->rx_max_pending = mac->hw->soc->dma_ring_size;
	ring->tx_max_pending = mac->hw->soc->dma_ring_size;
	ring->rx_pending = mac->hw->rx_ring[0].rx_ring_size;
	ring->tx_pending = mac->hw->tx_ring.tx_ring_size;
}