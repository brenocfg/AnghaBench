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
struct ravb_private {int /*<<< orphan*/ * num_tx_ring; int /*<<< orphan*/ * num_rx_ring; } ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  tx_max_pending; int /*<<< orphan*/  rx_max_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  BE_RX_RING_MAX ; 
 int /*<<< orphan*/  BE_TX_RING_MAX ; 
 size_t RAVB_BE ; 
 struct ravb_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ravb_get_ringparam(struct net_device *ndev,
			       struct ethtool_ringparam *ring)
{
	struct ravb_private *priv = netdev_priv(ndev);

	ring->rx_max_pending = BE_RX_RING_MAX;
	ring->tx_max_pending = BE_TX_RING_MAX;
	ring->rx_pending = priv->num_rx_ring[RAVB_BE];
	ring->tx_pending = priv->num_tx_ring[RAVB_BE];
}