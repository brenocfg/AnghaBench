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
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {scalar_t__ rx_pending; scalar_t__ tx_pending; scalar_t__ rx_jumbo_pending; scalar_t__ rx_mini_pending; } ;
struct ef4_nic {int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 scalar_t__ EF4_MAX_DMAQ_SIZE ; 
 scalar_t__ EF4_RXQ_MIN_ENT ; 
 int /*<<< orphan*/  EF4_TXQ_MIN_ENT (struct ef4_nic*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  drv ; 
 int ef4_realloc_channels (struct ef4_nic*,scalar_t__,scalar_t__) ; 
 scalar_t__ max (scalar_t__,int /*<<< orphan*/ ) ; 
 struct ef4_nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  netif_warn (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static int ef4_ethtool_set_ringparam(struct net_device *net_dev,
				     struct ethtool_ringparam *ring)
{
	struct ef4_nic *efx = netdev_priv(net_dev);
	u32 txq_entries;

	if (ring->rx_mini_pending || ring->rx_jumbo_pending ||
	    ring->rx_pending > EF4_MAX_DMAQ_SIZE ||
	    ring->tx_pending > EF4_MAX_DMAQ_SIZE)
		return -EINVAL;

	if (ring->rx_pending < EF4_RXQ_MIN_ENT) {
		netif_err(efx, drv, efx->net_dev,
			  "RX queues cannot be smaller than %u\n",
			  EF4_RXQ_MIN_ENT);
		return -EINVAL;
	}

	txq_entries = max(ring->tx_pending, EF4_TXQ_MIN_ENT(efx));
	if (txq_entries != ring->tx_pending)
		netif_warn(efx, drv, efx->net_dev,
			   "increasing TX queue size to minimum of %u\n",
			   txq_entries);

	return ef4_realloc_channels(efx, ring->rx_pending, txq_entries);
}