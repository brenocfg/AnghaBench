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
struct rtnl_link_stats64 {unsigned long tx_bytes; unsigned long tx_packets; unsigned long tx_dropped; unsigned long rx_bytes; unsigned long rx_packets; unsigned long rx_errors; } ;
struct net_device {int dummy; } ;
struct l2tp_eth {int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; } ;

/* Variables and functions */
 scalar_t__ atomic_long_read (int /*<<< orphan*/ *) ; 
 struct l2tp_eth* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void l2tp_eth_get_stats64(struct net_device *dev,
				 struct rtnl_link_stats64 *stats)
{
	struct l2tp_eth *priv = netdev_priv(dev);

	stats->tx_bytes   = (unsigned long) atomic_long_read(&priv->tx_bytes);
	stats->tx_packets = (unsigned long) atomic_long_read(&priv->tx_packets);
	stats->tx_dropped = (unsigned long) atomic_long_read(&priv->tx_dropped);
	stats->rx_bytes   = (unsigned long) atomic_long_read(&priv->rx_bytes);
	stats->rx_packets = (unsigned long) atomic_long_read(&priv->rx_packets);
	stats->rx_errors  = (unsigned long) atomic_long_read(&priv->rx_errors);

}