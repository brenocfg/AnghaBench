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
struct rtnl_link_stats64 {int /*<<< orphan*/  rx_nohandler; int /*<<< orphan*/  tx_compressed; int /*<<< orphan*/  rx_compressed; int /*<<< orphan*/  tx_window_errors; int /*<<< orphan*/  tx_heartbeat_errors; int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  tx_carrier_errors; int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  rx_missed_errors; int /*<<< orphan*/  rx_fifo_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_over_errors; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  collisions; int /*<<< orphan*/  multicast; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_packets; } ;
struct rtnl_link_stats {int /*<<< orphan*/  rx_nohandler; int /*<<< orphan*/  tx_compressed; int /*<<< orphan*/  rx_compressed; int /*<<< orphan*/  tx_window_errors; int /*<<< orphan*/  tx_heartbeat_errors; int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  tx_carrier_errors; int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  rx_missed_errors; int /*<<< orphan*/  rx_fifo_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_over_errors; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  collisions; int /*<<< orphan*/  multicast; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_packets; } ;

/* Variables and functions */

__attribute__((used)) static void copy_rtnl_link_stats(struct rtnl_link_stats *a,
				 const struct rtnl_link_stats64 *b)
{
	a->rx_packets = b->rx_packets;
	a->tx_packets = b->tx_packets;
	a->rx_bytes = b->rx_bytes;
	a->tx_bytes = b->tx_bytes;
	a->rx_errors = b->rx_errors;
	a->tx_errors = b->tx_errors;
	a->rx_dropped = b->rx_dropped;
	a->tx_dropped = b->tx_dropped;

	a->multicast = b->multicast;
	a->collisions = b->collisions;

	a->rx_length_errors = b->rx_length_errors;
	a->rx_over_errors = b->rx_over_errors;
	a->rx_crc_errors = b->rx_crc_errors;
	a->rx_frame_errors = b->rx_frame_errors;
	a->rx_fifo_errors = b->rx_fifo_errors;
	a->rx_missed_errors = b->rx_missed_errors;

	a->tx_aborted_errors = b->tx_aborted_errors;
	a->tx_carrier_errors = b->tx_carrier_errors;
	a->tx_fifo_errors = b->tx_fifo_errors;
	a->tx_heartbeat_errors = b->tx_heartbeat_errors;
	a->tx_window_errors = b->tx_window_errors;

	a->rx_compressed = b->rx_compressed;
	a->tx_compressed = b->tx_compressed;

	a->rx_nohandler = b->rx_nohandler;
}