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
struct rtnl_link_stats64 {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_4__ {int /*<<< orphan*/  bytes; int /*<<< orphan*/  packets; int /*<<< orphan*/  syncp; } ;
struct TYPE_3__ {int /*<<< orphan*/  bytes; int /*<<< orphan*/  packets; int /*<<< orphan*/  syncp; } ;
struct rhine_private {TYPE_2__ tx_stats; TYPE_1__ rx_stats; int /*<<< orphan*/  lock; } ;
struct net_device {int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 struct rhine_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_stats_to_stats64 (struct rtnl_link_stats64*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rhine_update_rx_crc_and_missed_errord (struct rhine_private*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 unsigned int u64_stats_fetch_begin_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ u64_stats_fetch_retry_irq (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void
rhine_get_stats64(struct net_device *dev, struct rtnl_link_stats64 *stats)
{
	struct rhine_private *rp = netdev_priv(dev);
	unsigned int start;

	spin_lock_bh(&rp->lock);
	rhine_update_rx_crc_and_missed_errord(rp);
	spin_unlock_bh(&rp->lock);

	netdev_stats_to_stats64(stats, &dev->stats);

	do {
		start = u64_stats_fetch_begin_irq(&rp->rx_stats.syncp);
		stats->rx_packets = rp->rx_stats.packets;
		stats->rx_bytes = rp->rx_stats.bytes;
	} while (u64_stats_fetch_retry_irq(&rp->rx_stats.syncp, start));

	do {
		start = u64_stats_fetch_begin_irq(&rp->tx_stats.syncp);
		stats->tx_packets = rp->tx_stats.packets;
		stats->tx_bytes = rp->tx_stats.bytes;
	} while (u64_stats_fetch_retry_irq(&rp->tx_stats.syncp, start));
}