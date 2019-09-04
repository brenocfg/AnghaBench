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
struct fsf_qtcb_bottom_port {scalar_t__ output_mb; scalar_t__ input_mb; scalar_t__ control_requests; scalar_t__ output_requests; scalar_t__ input_requests; scalar_t__ invalid_crcs; scalar_t__ invalid_tx_words; scalar_t__ psp_error_counts; scalar_t__ loss_of_signal; scalar_t__ loss_of_sync; scalar_t__ link_failure; scalar_t__ dumped_frames; scalar_t__ error_frames; scalar_t__ nos; scalar_t__ lip; scalar_t__ rx_words; scalar_t__ rx_frames; scalar_t__ tx_words; scalar_t__ tx_frames; scalar_t__ seconds_since_last_reset; } ;
struct fc_host_statistics {scalar_t__ fcp_output_megabytes; scalar_t__ fcp_input_megabytes; scalar_t__ fcp_control_requests; scalar_t__ fcp_output_requests; scalar_t__ fcp_input_requests; scalar_t__ invalid_crc_count; scalar_t__ invalid_tx_word_count; scalar_t__ prim_seq_protocol_err_count; scalar_t__ loss_of_signal_count; scalar_t__ loss_of_sync_count; scalar_t__ link_failure_count; scalar_t__ dumped_frames; scalar_t__ error_frames; scalar_t__ nos_count; scalar_t__ lip_count; scalar_t__ rx_words; scalar_t__ rx_frames; scalar_t__ tx_words; scalar_t__ tx_frames; scalar_t__ seconds_since_last_reset; } ;

/* Variables and functions */

__attribute__((used)) static void zfcp_scsi_adjust_fc_host_stats(struct fc_host_statistics *fc_stats,
					   struct fsf_qtcb_bottom_port *data,
					   struct fsf_qtcb_bottom_port *old)
{
	fc_stats->seconds_since_last_reset =
		data->seconds_since_last_reset - old->seconds_since_last_reset;
	fc_stats->tx_frames = data->tx_frames - old->tx_frames;
	fc_stats->tx_words = data->tx_words - old->tx_words;
	fc_stats->rx_frames = data->rx_frames - old->rx_frames;
	fc_stats->rx_words = data->rx_words - old->rx_words;
	fc_stats->lip_count = data->lip - old->lip;
	fc_stats->nos_count = data->nos - old->nos;
	fc_stats->error_frames = data->error_frames - old->error_frames;
	fc_stats->dumped_frames = data->dumped_frames - old->dumped_frames;
	fc_stats->link_failure_count = data->link_failure - old->link_failure;
	fc_stats->loss_of_sync_count = data->loss_of_sync - old->loss_of_sync;
	fc_stats->loss_of_signal_count =
		data->loss_of_signal - old->loss_of_signal;
	fc_stats->prim_seq_protocol_err_count =
		data->psp_error_counts - old->psp_error_counts;
	fc_stats->invalid_tx_word_count =
		data->invalid_tx_words - old->invalid_tx_words;
	fc_stats->invalid_crc_count = data->invalid_crcs - old->invalid_crcs;
	fc_stats->fcp_input_requests =
		data->input_requests - old->input_requests;
	fc_stats->fcp_output_requests =
		data->output_requests - old->output_requests;
	fc_stats->fcp_control_requests =
		data->control_requests - old->control_requests;
	fc_stats->fcp_input_megabytes = data->input_mb - old->input_mb;
	fc_stats->fcp_output_megabytes = data->output_mb - old->output_mb;
}