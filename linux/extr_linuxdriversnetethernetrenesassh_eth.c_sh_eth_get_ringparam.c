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
struct sh_eth_private {int /*<<< orphan*/  num_tx_ring; int /*<<< orphan*/  num_rx_ring; } ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  tx_max_pending; int /*<<< orphan*/  rx_max_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_RING_MAX ; 
 int /*<<< orphan*/  TX_RING_MAX ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void sh_eth_get_ringparam(struct net_device *ndev,
				 struct ethtool_ringparam *ring)
{
	struct sh_eth_private *mdp = netdev_priv(ndev);

	ring->rx_max_pending = RX_RING_MAX;
	ring->tx_max_pending = TX_RING_MAX;
	ring->rx_pending = mdp->num_rx_ring;
	ring->tx_pending = mdp->num_tx_ring;
}