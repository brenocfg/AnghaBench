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
struct rtnl_link_stats64 {scalar_t__ tx_window_errors; scalar_t__ tx_aborted_errors; scalar_t__ tx_fifo_errors; scalar_t__ tx_errors; int /*<<< orphan*/  rx_missed_errors; int /*<<< orphan*/  rx_over_errors; scalar_t__ rx_frame_errors; scalar_t__ rx_crc_errors; scalar_t__ rx_length_errors; int /*<<< orphan*/  rx_fifo_errors; scalar_t__ rx_errors; scalar_t__ collisions; int /*<<< orphan*/  multicast; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_packets; } ;
struct net_device {int dummy; } ;
struct emac_stats {int tx_2_col; int /*<<< orphan*/  lock; scalar_t__ tx_late_col; scalar_t__ tx_abort_col; scalar_t__ tx_underrun; scalar_t__ tx_trunc; int /*<<< orphan*/  rx_rxf_ov; scalar_t__ rx_align_err; scalar_t__ rx_fcs_err; scalar_t__ rx_len_err; scalar_t__ rx_sz_ov; scalar_t__ rx_frag; scalar_t__ tx_1_col; int /*<<< orphan*/  rx_mcast; int /*<<< orphan*/  tx_byte_cnt; int /*<<< orphan*/  rx_byte_cnt; int /*<<< orphan*/  tx_ok; int /*<<< orphan*/  rx_ok; } ;
struct emac_adapter {struct emac_stats stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  emac_update_hw_stats (struct emac_adapter*) ; 
 struct emac_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void emac_get_stats64(struct net_device *netdev,
			     struct rtnl_link_stats64 *net_stats)
{
	struct emac_adapter *adpt = netdev_priv(netdev);
	struct emac_stats *stats = &adpt->stats;

	spin_lock(&stats->lock);

	emac_update_hw_stats(adpt);

	/* return parsed statistics */
	net_stats->rx_packets = stats->rx_ok;
	net_stats->tx_packets = stats->tx_ok;
	net_stats->rx_bytes = stats->rx_byte_cnt;
	net_stats->tx_bytes = stats->tx_byte_cnt;
	net_stats->multicast = stats->rx_mcast;
	net_stats->collisions = stats->tx_1_col + stats->tx_2_col * 2 +
				stats->tx_late_col + stats->tx_abort_col;

	net_stats->rx_errors = stats->rx_frag + stats->rx_fcs_err +
			       stats->rx_len_err + stats->rx_sz_ov +
			       stats->rx_align_err;
	net_stats->rx_fifo_errors = stats->rx_rxf_ov;
	net_stats->rx_length_errors = stats->rx_len_err;
	net_stats->rx_crc_errors = stats->rx_fcs_err;
	net_stats->rx_frame_errors = stats->rx_align_err;
	net_stats->rx_over_errors = stats->rx_rxf_ov;
	net_stats->rx_missed_errors = stats->rx_rxf_ov;

	net_stats->tx_errors = stats->tx_late_col + stats->tx_abort_col +
			       stats->tx_underrun + stats->tx_trunc;
	net_stats->tx_fifo_errors = stats->tx_underrun;
	net_stats->tx_aborted_errors = stats->tx_abort_col;
	net_stats->tx_window_errors = stats->tx_late_col;

	spin_unlock(&stats->lock);
}