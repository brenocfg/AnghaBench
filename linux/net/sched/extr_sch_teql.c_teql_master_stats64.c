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
struct teql_master {int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct rtnl_link_stats64 {int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct teql_master* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void teql_master_stats64(struct net_device *dev,
				struct rtnl_link_stats64 *stats)
{
	struct teql_master *m = netdev_priv(dev);

	stats->tx_packets	= m->tx_packets;
	stats->tx_bytes		= m->tx_bytes;
	stats->tx_errors	= m->tx_errors;
	stats->tx_dropped	= m->tx_dropped;
}