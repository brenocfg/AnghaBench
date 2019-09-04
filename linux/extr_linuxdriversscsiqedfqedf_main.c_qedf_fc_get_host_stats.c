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
struct qedf_ctx {int /*<<< orphan*/  stats_mutex; scalar_t__ alloc_failures; scalar_t__ packet_aborts; scalar_t__ control_requests; scalar_t__ output_requests; scalar_t__ input_requests; int /*<<< orphan*/  cdev; int /*<<< orphan*/  dbg_ctx; } ;
struct qed_fcoe_stats {int fcoe_rx_byte_cnt; int fcoe_tx_byte_cnt; scalar_t__ fcoe_silent_drop_total_pkt_cnt; scalar_t__ fcoe_silent_drop_pkt_crc_error_cnt; scalar_t__ fcoe_rx_other_pkt_cnt; scalar_t__ fcoe_rx_xfer_pkt_cnt; scalar_t__ fcoe_rx_data_pkt_cnt; scalar_t__ fcoe_tx_other_pkt_cnt; scalar_t__ fcoe_tx_xfer_pkt_cnt; scalar_t__ fcoe_tx_data_pkt_cnt; } ;
struct fc_lport {scalar_t__ vport; } ;
struct fc_host_statistics {int rx_words; int tx_words; int /*<<< orphan*/  fcp_frame_alloc_failures; int /*<<< orphan*/  fcp_packet_aborts; int /*<<< orphan*/  fcp_control_requests; int /*<<< orphan*/  fcp_output_requests; int /*<<< orphan*/  fcp_input_requests; int /*<<< orphan*/  error_frames; scalar_t__ dumped_frames; int /*<<< orphan*/  invalid_crc_count; int /*<<< orphan*/  fcp_output_megabytes; int /*<<< orphan*/  fcp_input_megabytes; int /*<<< orphan*/  rx_frames; int /*<<< orphan*/  tx_frames; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_stats ) (int /*<<< orphan*/ ,struct qed_fcoe_stats*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ do_div (int,int) ; 
 struct fc_host_statistics* fc_get_host_stats (struct Scsi_Host*) ; 
 int /*<<< orphan*/  kfree (struct qed_fcoe_stats*) ; 
 struct qed_fcoe_stats* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct qedf_ctx* lport_priv (struct fc_lport*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* qed_ops ; 
 struct fc_lport* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct qed_fcoe_stats*) ; 

__attribute__((used)) static struct fc_host_statistics *qedf_fc_get_host_stats(struct Scsi_Host
	*shost)
{
	struct fc_host_statistics *qedf_stats;
	struct fc_lport *lport = shost_priv(shost);
	struct qedf_ctx *qedf = lport_priv(lport);
	struct qed_fcoe_stats *fw_fcoe_stats;

	qedf_stats = fc_get_host_stats(shost);

	/* We don't collect offload stats for specific NPIV ports */
	if (lport->vport)
		goto out;

	fw_fcoe_stats = kmalloc(sizeof(struct qed_fcoe_stats), GFP_KERNEL);
	if (!fw_fcoe_stats) {
		QEDF_ERR(&(qedf->dbg_ctx), "Could not allocate memory for "
		    "fw_fcoe_stats.\n");
		goto out;
	}

	mutex_lock(&qedf->stats_mutex);

	/* Query firmware for offload stats */
	qed_ops->get_stats(qedf->cdev, fw_fcoe_stats);

	/*
	 * The expectation is that we add our offload stats to the stats
	 * being maintained by libfc each time the fc_get_host_status callback
	 * is invoked. The additions are not carried over for each call to
	 * the fc_get_host_stats callback.
	 */
	qedf_stats->tx_frames += fw_fcoe_stats->fcoe_tx_data_pkt_cnt +
	    fw_fcoe_stats->fcoe_tx_xfer_pkt_cnt +
	    fw_fcoe_stats->fcoe_tx_other_pkt_cnt;
	qedf_stats->rx_frames += fw_fcoe_stats->fcoe_rx_data_pkt_cnt +
	    fw_fcoe_stats->fcoe_rx_xfer_pkt_cnt +
	    fw_fcoe_stats->fcoe_rx_other_pkt_cnt;
	qedf_stats->fcp_input_megabytes +=
	    do_div(fw_fcoe_stats->fcoe_rx_byte_cnt, 1000000);
	qedf_stats->fcp_output_megabytes +=
	    do_div(fw_fcoe_stats->fcoe_tx_byte_cnt, 1000000);
	qedf_stats->rx_words += fw_fcoe_stats->fcoe_rx_byte_cnt / 4;
	qedf_stats->tx_words += fw_fcoe_stats->fcoe_tx_byte_cnt / 4;
	qedf_stats->invalid_crc_count +=
	    fw_fcoe_stats->fcoe_silent_drop_pkt_crc_error_cnt;
	qedf_stats->dumped_frames =
	    fw_fcoe_stats->fcoe_silent_drop_total_pkt_cnt;
	qedf_stats->error_frames +=
	    fw_fcoe_stats->fcoe_silent_drop_total_pkt_cnt;
	qedf_stats->fcp_input_requests += qedf->input_requests;
	qedf_stats->fcp_output_requests += qedf->output_requests;
	qedf_stats->fcp_control_requests += qedf->control_requests;
	qedf_stats->fcp_packet_aborts += qedf->packet_aborts;
	qedf_stats->fcp_frame_alloc_failures += qedf->alloc_failures;

	mutex_unlock(&qedf->stats_mutex);
	kfree(fw_fcoe_stats);
out:
	return qedf_stats;
}