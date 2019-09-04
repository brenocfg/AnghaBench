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
typedef  int /*<<< orphan*/  u64 ;
struct ravb_private {int /*<<< orphan*/ * dirty_tx; int /*<<< orphan*/ * dirty_rx; int /*<<< orphan*/ * cur_tx; int /*<<< orphan*/ * cur_rx; struct net_device_stats* stats; } ;
struct net_device_stats {int /*<<< orphan*/  rx_over_errors; int /*<<< orphan*/  rx_missed_errors; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  multicast; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_packets; } ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;

/* Variables and functions */
 int NUM_RX_QUEUE ; 
 int RAVB_BE ; 
 struct ravb_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ravb_get_ethtool_stats(struct net_device *ndev,
				   struct ethtool_stats *estats, u64 *data)
{
	struct ravb_private *priv = netdev_priv(ndev);
	int i = 0;
	int q;

	/* Device-specific stats */
	for (q = RAVB_BE; q < NUM_RX_QUEUE; q++) {
		struct net_device_stats *stats = &priv->stats[q];

		data[i++] = priv->cur_rx[q];
		data[i++] = priv->cur_tx[q];
		data[i++] = priv->dirty_rx[q];
		data[i++] = priv->dirty_tx[q];
		data[i++] = stats->rx_packets;
		data[i++] = stats->tx_packets;
		data[i++] = stats->rx_bytes;
		data[i++] = stats->tx_bytes;
		data[i++] = stats->multicast;
		data[i++] = stats->rx_errors;
		data[i++] = stats->rx_crc_errors;
		data[i++] = stats->rx_frame_errors;
		data[i++] = stats->rx_length_errors;
		data[i++] = stats->rx_missed_errors;
		data[i++] = stats->rx_over_errors;
	}
}