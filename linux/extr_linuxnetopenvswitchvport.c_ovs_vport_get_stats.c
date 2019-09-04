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
struct vport {int /*<<< orphan*/  dev; } ;
struct rtnl_link_stats64 {int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  rx_errors; } ;
struct ovs_vport_stats {int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  rx_errors; } ;

/* Variables and functions */
 struct rtnl_link_stats64* dev_get_stats (int /*<<< orphan*/ ,struct rtnl_link_stats64*) ; 

void ovs_vport_get_stats(struct vport *vport, struct ovs_vport_stats *stats)
{
	const struct rtnl_link_stats64 *dev_stats;
	struct rtnl_link_stats64 temp;

	dev_stats = dev_get_stats(vport->dev, &temp);
	stats->rx_errors  = dev_stats->rx_errors;
	stats->tx_errors  = dev_stats->tx_errors;
	stats->tx_dropped = dev_stats->tx_dropped;
	stats->rx_dropped = dev_stats->rx_dropped;

	stats->rx_bytes	  = dev_stats->rx_bytes;
	stats->rx_packets = dev_stats->rx_packets;
	stats->tx_bytes	  = dev_stats->tx_bytes;
	stats->tx_packets = dev_stats->tx_packets;
}