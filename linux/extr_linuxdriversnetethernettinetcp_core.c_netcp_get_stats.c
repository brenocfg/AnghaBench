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
typedef  void* u64 ;
struct rtnl_link_stats64 {int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_errors; void* tx_bytes; void* tx_packets; void* rx_bytes; void* rx_packets; } ;
struct netcp_stats {int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_errors; void* tx_bytes; void* tx_packets; int /*<<< orphan*/  syncp_tx; void* rx_bytes; void* rx_packets; int /*<<< orphan*/  syncp_rx; } ;
struct netcp_intf {struct netcp_stats stats; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct netcp_intf* netdev_priv (struct net_device*) ; 
 unsigned int u64_stats_fetch_begin_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ u64_stats_fetch_retry_irq (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void
netcp_get_stats(struct net_device *ndev, struct rtnl_link_stats64 *stats)
{
	struct netcp_intf *netcp = netdev_priv(ndev);
	struct netcp_stats *p = &netcp->stats;
	u64 rxpackets, rxbytes, txpackets, txbytes;
	unsigned int start;

	do {
		start = u64_stats_fetch_begin_irq(&p->syncp_rx);
		rxpackets       = p->rx_packets;
		rxbytes         = p->rx_bytes;
	} while (u64_stats_fetch_retry_irq(&p->syncp_rx, start));

	do {
		start = u64_stats_fetch_begin_irq(&p->syncp_tx);
		txpackets       = p->tx_packets;
		txbytes         = p->tx_bytes;
	} while (u64_stats_fetch_retry_irq(&p->syncp_tx, start));

	stats->rx_packets = rxpackets;
	stats->rx_bytes = rxbytes;
	stats->tx_packets = txpackets;
	stats->tx_bytes = txbytes;

	/* The following are stored as 32 bit */
	stats->rx_errors = p->rx_errors;
	stats->rx_dropped = p->rx_dropped;
	stats->tx_dropped = p->tx_dropped;
}