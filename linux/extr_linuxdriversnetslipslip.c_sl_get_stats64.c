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
struct rtnl_link_stats64 {int /*<<< orphan*/  rx_over_errors; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_packets; } ;
struct net_device_stats {int /*<<< orphan*/  rx_over_errors; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_packets; } ;
struct net_device {struct net_device_stats stats; } ;

/* Variables and functions */

__attribute__((used)) static void
sl_get_stats64(struct net_device *dev, struct rtnl_link_stats64 *stats)
{
	struct net_device_stats *devstats = &dev->stats;
#ifdef SL_INCLUDE_CSLIP
	struct slip *sl = netdev_priv(dev);
	struct slcompress *comp = sl->slcomp;
#endif
	stats->rx_packets     = devstats->rx_packets;
	stats->tx_packets     = devstats->tx_packets;
	stats->rx_bytes       = devstats->rx_bytes;
	stats->tx_bytes       = devstats->tx_bytes;
	stats->rx_dropped     = devstats->rx_dropped;
	stats->tx_dropped     = devstats->tx_dropped;
	stats->tx_errors      = devstats->tx_errors;
	stats->rx_errors      = devstats->rx_errors;
	stats->rx_over_errors = devstats->rx_over_errors;

#ifdef SL_INCLUDE_CSLIP
	if (comp) {
		/* Generic compressed statistics */
		stats->rx_compressed   = comp->sls_i_compressed;
		stats->tx_compressed   = comp->sls_o_compressed;

		/* Are we really still needs this? */
		stats->rx_fifo_errors += comp->sls_i_compressed;
		stats->rx_dropped     += comp->sls_i_tossed;
		stats->tx_fifo_errors += comp->sls_o_compressed;
		stats->collisions     += comp->sls_o_misses;
	}
#endif
}