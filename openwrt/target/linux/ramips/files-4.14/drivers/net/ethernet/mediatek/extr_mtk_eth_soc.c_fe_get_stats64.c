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
struct rtnl_link_stats64 {int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_over_errors; scalar_t__ rx_length_errors; int /*<<< orphan*/  collisions; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_packets; } ;
struct net_device {int /*<<< orphan*/  stats; } ;
struct fe_priv {TYPE_2__* netdev; struct fe_hw_stats* hw_stats; } ;
struct fe_hw_stats {int /*<<< orphan*/  tx_skip; int /*<<< orphan*/  rx_checksum_errors; int /*<<< orphan*/  rx_fcs_errors; int /*<<< orphan*/  rx_overflow; scalar_t__ rx_long_errors; scalar_t__ rx_short_errors; int /*<<< orphan*/  tx_collisions; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  syncp; int /*<<< orphan*/  stats_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  tx_errors; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 size_t FE_REG_FE_COUNTER_BASE ; 
 unsigned int* fe_reg_table ; 
 int /*<<< orphan*/  fe_stats_update (struct fe_priv*) ; 
 struct fe_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_stats_to_stats64 (struct rtnl_link_stats64*,int /*<<< orphan*/ *) ; 
 scalar_t__ netif_device_present (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 scalar_t__ spin_trylock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 unsigned int u64_stats_fetch_begin_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ u64_stats_fetch_retry_irq (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void fe_get_stats64(struct net_device *dev,
				struct rtnl_link_stats64 *storage)
{
	struct fe_priv *priv = netdev_priv(dev);
	struct fe_hw_stats *hwstats = priv->hw_stats;
	unsigned int base = fe_reg_table[FE_REG_FE_COUNTER_BASE];
	unsigned int start;

	if (!base) {
		netdev_stats_to_stats64(storage, &dev->stats);
		return;
	}

	if (netif_running(dev) && netif_device_present(dev)) {
		if (spin_trylock_bh(&hwstats->stats_lock)) {
			fe_stats_update(priv);
			spin_unlock_bh(&hwstats->stats_lock);
		}
	}

	do {
		start = u64_stats_fetch_begin_irq(&hwstats->syncp);
		storage->rx_packets = hwstats->rx_packets;
		storage->tx_packets = hwstats->tx_packets;
		storage->rx_bytes = hwstats->rx_bytes;
		storage->tx_bytes = hwstats->tx_bytes;
		storage->collisions = hwstats->tx_collisions;
		storage->rx_length_errors = hwstats->rx_short_errors +
			hwstats->rx_long_errors;
		storage->rx_over_errors = hwstats->rx_overflow;
		storage->rx_crc_errors = hwstats->rx_fcs_errors;
		storage->rx_errors = hwstats->rx_checksum_errors;
		storage->tx_aborted_errors = hwstats->tx_skip;
	} while (u64_stats_fetch_retry_irq(&hwstats->syncp, start));

	storage->tx_errors = priv->netdev->stats.tx_errors;
	storage->rx_dropped = priv->netdev->stats.rx_dropped;
	storage->tx_dropped = priv->netdev->stats.tx_dropped;
}