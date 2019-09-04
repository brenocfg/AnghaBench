#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ rx_missed_errors; scalar_t__ rx_crc_errors; scalar_t__ rx_over_errors; scalar_t__ rx_length_errors; int /*<<< orphan*/  tx_errors; scalar_t__ rx_errors; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  tx_packets; } ;
struct tbnet {TYPE_1__ stats; } ;
struct rtnl_link_stats64 {scalar_t__ rx_missed_errors; scalar_t__ rx_crc_errors; scalar_t__ rx_over_errors; scalar_t__ rx_length_errors; int /*<<< orphan*/  tx_errors; scalar_t__ rx_errors; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  tx_packets; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct tbnet* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void tbnet_get_stats64(struct net_device *dev,
			      struct rtnl_link_stats64 *stats)
{
	struct tbnet *net = netdev_priv(dev);

	stats->tx_packets = net->stats.tx_packets;
	stats->rx_packets = net->stats.rx_packets;
	stats->tx_bytes = net->stats.tx_bytes;
	stats->rx_bytes = net->stats.rx_bytes;
	stats->rx_errors = net->stats.rx_errors + net->stats.rx_length_errors +
		net->stats.rx_over_errors + net->stats.rx_crc_errors +
		net->stats.rx_missed_errors;
	stats->tx_errors = net->stats.tx_errors;
	stats->rx_length_errors = net->stats.rx_length_errors;
	stats->rx_over_errors = net->stats.rx_over_errors;
	stats->rx_crc_errors = net->stats.rx_crc_errors;
	stats->rx_missed_errors = net->stats.rx_missed_errors;
}