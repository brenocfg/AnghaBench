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
typedef  int u64 ;
struct rtnl_link_stats64 {int rx_packets; int tx_packets; int rx_bytes; int tx_bytes; int rx_dropped; int multicast; int rx_length_errors; int rx_crc_errors; int rx_frame_errors; int rx_fifo_errors; int rx_errors; } ;
struct falcon_nic_data {int* stats; int stats_pending; int /*<<< orphan*/  stats_disable_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct ef4_nic {TYPE_1__ stats_buffer; struct falcon_nic_data* nic_data; } ;
typedef  int /*<<< orphan*/  ef4_oword_t ;

/* Variables and functions */
 scalar_t__ EF4_OWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FALCON_STAT_COUNT ; 
 size_t FALCON_STAT_rx_align_error ; 
 size_t FALCON_STAT_rx_bad ; 
 size_t FALCON_STAT_rx_bad_bytes ; 
 size_t FALCON_STAT_rx_bytes ; 
 size_t FALCON_STAT_rx_control ; 
 size_t FALCON_STAT_rx_good_bytes ; 
 size_t FALCON_STAT_rx_gtjumbo ; 
 size_t FALCON_STAT_rx_length_error ; 
 size_t FALCON_STAT_rx_multicast ; 
 size_t FALCON_STAT_rx_nodesc_drop_cnt ; 
 size_t FALCON_STAT_rx_overflow ; 
 size_t FALCON_STAT_rx_packets ; 
 size_t FALCON_STAT_rx_symbol_error ; 
 size_t FALCON_STAT_tx_bytes ; 
 size_t FALCON_STAT_tx_packets ; 
 scalar_t__ FALCON_XMAC_STATS_DMA_FLAG (struct ef4_nic*) ; 
 int /*<<< orphan*/  FRF_AB_RX_NODESC_DROP_CNT ; 
 int /*<<< orphan*/  FR_AZ_RX_NODESC_DROP ; 
 size_t GENERIC_STAT_rx_nodesc_trunc ; 
 size_t GENERIC_STAT_rx_noskb_drops ; 
 int /*<<< orphan*/  ef4_nic_update_stats (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ef4_reado (struct ef4_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ef4_update_diff_stat (int*,int) ; 
 int /*<<< orphan*/  ef4_update_sw_stats (struct ef4_nic*,int*) ; 
 int /*<<< orphan*/  falcon_stat_desc ; 
 int /*<<< orphan*/  falcon_stat_mask ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  rmb () ; 

__attribute__((used)) static size_t falcon_update_nic_stats(struct ef4_nic *efx, u64 *full_stats,
				      struct rtnl_link_stats64 *core_stats)
{
	struct falcon_nic_data *nic_data = efx->nic_data;
	u64 *stats = nic_data->stats;
	ef4_oword_t cnt;

	if (!nic_data->stats_disable_count) {
		ef4_reado(efx, &cnt, FR_AZ_RX_NODESC_DROP);
		stats[FALCON_STAT_rx_nodesc_drop_cnt] +=
			EF4_OWORD_FIELD(cnt, FRF_AB_RX_NODESC_DROP_CNT);

		if (nic_data->stats_pending &&
		    FALCON_XMAC_STATS_DMA_FLAG(efx)) {
			nic_data->stats_pending = false;
			rmb(); /* read the done flag before the stats */
			ef4_nic_update_stats(
				falcon_stat_desc, FALCON_STAT_COUNT,
				falcon_stat_mask,
				stats, efx->stats_buffer.addr, true);
		}

		/* Update derived statistic */
		ef4_update_diff_stat(&stats[FALCON_STAT_rx_bad_bytes],
				     stats[FALCON_STAT_rx_bytes] -
				     stats[FALCON_STAT_rx_good_bytes] -
				     stats[FALCON_STAT_rx_control] * 64);
		ef4_update_sw_stats(efx, stats);
	}

	if (full_stats)
		memcpy(full_stats, stats, sizeof(u64) * FALCON_STAT_COUNT);

	if (core_stats) {
		core_stats->rx_packets = stats[FALCON_STAT_rx_packets];
		core_stats->tx_packets = stats[FALCON_STAT_tx_packets];
		core_stats->rx_bytes = stats[FALCON_STAT_rx_bytes];
		core_stats->tx_bytes = stats[FALCON_STAT_tx_bytes];
		core_stats->rx_dropped = stats[FALCON_STAT_rx_nodesc_drop_cnt] +
					 stats[GENERIC_STAT_rx_nodesc_trunc] +
					 stats[GENERIC_STAT_rx_noskb_drops];
		core_stats->multicast = stats[FALCON_STAT_rx_multicast];
		core_stats->rx_length_errors =
			stats[FALCON_STAT_rx_gtjumbo] +
			stats[FALCON_STAT_rx_length_error];
		core_stats->rx_crc_errors = stats[FALCON_STAT_rx_bad];
		core_stats->rx_frame_errors = stats[FALCON_STAT_rx_align_error];
		core_stats->rx_fifo_errors = stats[FALCON_STAT_rx_overflow];

		core_stats->rx_errors = (core_stats->rx_length_errors +
					 core_stats->rx_crc_errors +
					 core_stats->rx_frame_errors +
					 stats[FALCON_STAT_rx_symbol_error]);
	}

	return FALCON_STAT_COUNT;
}