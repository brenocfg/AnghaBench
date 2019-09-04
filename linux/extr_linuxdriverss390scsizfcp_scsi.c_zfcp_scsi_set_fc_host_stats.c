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
struct fsf_qtcb_bottom_port {int /*<<< orphan*/  output_mb; int /*<<< orphan*/  input_mb; int /*<<< orphan*/  control_requests; int /*<<< orphan*/  output_requests; int /*<<< orphan*/  input_requests; int /*<<< orphan*/  invalid_crcs; int /*<<< orphan*/  invalid_tx_words; int /*<<< orphan*/  psp_error_counts; int /*<<< orphan*/  loss_of_signal; int /*<<< orphan*/  loss_of_sync; int /*<<< orphan*/  link_failure; int /*<<< orphan*/  dumped_frames; int /*<<< orphan*/  error_frames; int /*<<< orphan*/  nos; int /*<<< orphan*/  lip; int /*<<< orphan*/  rx_words; int /*<<< orphan*/  rx_frames; int /*<<< orphan*/  tx_words; int /*<<< orphan*/  tx_frames; int /*<<< orphan*/  seconds_since_last_reset; } ;
struct fc_host_statistics {int /*<<< orphan*/  fcp_output_megabytes; int /*<<< orphan*/  fcp_input_megabytes; int /*<<< orphan*/  fcp_control_requests; int /*<<< orphan*/  fcp_output_requests; int /*<<< orphan*/  fcp_input_requests; int /*<<< orphan*/  invalid_crc_count; int /*<<< orphan*/  invalid_tx_word_count; int /*<<< orphan*/  prim_seq_protocol_err_count; int /*<<< orphan*/  loss_of_signal_count; int /*<<< orphan*/  loss_of_sync_count; int /*<<< orphan*/  link_failure_count; int /*<<< orphan*/  dumped_frames; int /*<<< orphan*/  error_frames; int /*<<< orphan*/  nos_count; int /*<<< orphan*/  lip_count; int /*<<< orphan*/  rx_words; int /*<<< orphan*/  rx_frames; int /*<<< orphan*/  tx_words; int /*<<< orphan*/  tx_frames; int /*<<< orphan*/  seconds_since_last_reset; } ;

/* Variables and functions */

__attribute__((used)) static void zfcp_scsi_set_fc_host_stats(struct fc_host_statistics *fc_stats,
					struct fsf_qtcb_bottom_port *data)
{
	fc_stats->seconds_since_last_reset = data->seconds_since_last_reset;
	fc_stats->tx_frames = data->tx_frames;
	fc_stats->tx_words = data->tx_words;
	fc_stats->rx_frames = data->rx_frames;
	fc_stats->rx_words = data->rx_words;
	fc_stats->lip_count = data->lip;
	fc_stats->nos_count = data->nos;
	fc_stats->error_frames = data->error_frames;
	fc_stats->dumped_frames = data->dumped_frames;
	fc_stats->link_failure_count = data->link_failure;
	fc_stats->loss_of_sync_count = data->loss_of_sync;
	fc_stats->loss_of_signal_count = data->loss_of_signal;
	fc_stats->prim_seq_protocol_err_count = data->psp_error_counts;
	fc_stats->invalid_tx_word_count = data->invalid_tx_words;
	fc_stats->invalid_crc_count = data->invalid_crcs;
	fc_stats->fcp_input_requests = data->input_requests;
	fc_stats->fcp_output_requests = data->output_requests;
	fc_stats->fcp_control_requests = data->control_requests;
	fc_stats->fcp_input_megabytes = data->input_mb;
	fc_stats->fcp_output_megabytes = data->output_mb;
}