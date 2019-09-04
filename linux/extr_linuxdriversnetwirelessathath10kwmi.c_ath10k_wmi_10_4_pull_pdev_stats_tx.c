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
struct wmi_10_4_pdev_stats_tx {int /*<<< orphan*/  mpdus_expired; int /*<<< orphan*/  mpdus_hw_filter; int /*<<< orphan*/  mpdus_ack_failed; int /*<<< orphan*/  mpdus_truncated; int /*<<< orphan*/  mpdus_sw_flush; int /*<<< orphan*/  mu_seq_posted; int /*<<< orphan*/  seq_restarted; int /*<<< orphan*/  seq_completed; int /*<<< orphan*/  seq_failed_queueing; int /*<<< orphan*/  seq_posted; int /*<<< orphan*/  hw_paused; int /*<<< orphan*/  txop_ovf; int /*<<< orphan*/  phy_underrun; int /*<<< orphan*/  pdev_resets; int /*<<< orphan*/  pdev_tx_timeout; int /*<<< orphan*/  pdev_cont_xretry; int /*<<< orphan*/  illgl_rate_phy_err; int /*<<< orphan*/  sw_retry_failure; int /*<<< orphan*/  self_triggers; int /*<<< orphan*/  data_rc; int /*<<< orphan*/  tx_ko; int /*<<< orphan*/  mpdus_requed; int /*<<< orphan*/  tx_abort; int /*<<< orphan*/  underrun; int /*<<< orphan*/  hw_reaped; int /*<<< orphan*/  hw_queued; int /*<<< orphan*/  local_freed; int /*<<< orphan*/  local_enqued; int /*<<< orphan*/  wmm_drop; int /*<<< orphan*/  mpdu_enqued; int /*<<< orphan*/  msdu_enqued; int /*<<< orphan*/  comp_delivered; int /*<<< orphan*/  comp_queued; } ;
struct ath10k_fw_stats_pdev {void* mpdus_expired; void* mpdus_hw_filter; void* mpdus_ack_failed; void* mpdus_truncated; void* mpdus_sw_flush; void* mu_seq_posted; void* seq_restarted; void* seq_completed; void* seq_failed_queueing; void* seq_posted; void* hw_paused; void* txop_ovf; void* phy_underrun; void* pdev_resets; void* pdev_tx_timeout; void* pdev_cont_xretry; void* illgl_rate_phy_err; void* sw_retry_failure; void* self_triggers; void* data_rc; void* tx_ko; void* mpdus_requed; void* tx_abort; void* underrun; void* hw_reaped; void* hw_queued; void* local_freed; void* local_enqued; void* wmm_drop; void* mpdu_enqued; void* msdu_enqued; void* comp_delivered; void* comp_queued; } ;

/* Variables and functions */
 void* __le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ath10k_wmi_10_4_pull_pdev_stats_tx(const struct wmi_10_4_pdev_stats_tx *src,
				   struct ath10k_fw_stats_pdev *dst)
{
	dst->comp_queued = __le32_to_cpu(src->comp_queued);
	dst->comp_delivered = __le32_to_cpu(src->comp_delivered);
	dst->msdu_enqued = __le32_to_cpu(src->msdu_enqued);
	dst->mpdu_enqued = __le32_to_cpu(src->mpdu_enqued);
	dst->wmm_drop = __le32_to_cpu(src->wmm_drop);
	dst->local_enqued = __le32_to_cpu(src->local_enqued);
	dst->local_freed = __le32_to_cpu(src->local_freed);
	dst->hw_queued = __le32_to_cpu(src->hw_queued);
	dst->hw_reaped = __le32_to_cpu(src->hw_reaped);
	dst->underrun = __le32_to_cpu(src->underrun);
	dst->tx_abort = __le32_to_cpu(src->tx_abort);
	dst->mpdus_requed = __le32_to_cpu(src->mpdus_requed);
	dst->tx_ko = __le32_to_cpu(src->tx_ko);
	dst->data_rc = __le32_to_cpu(src->data_rc);
	dst->self_triggers = __le32_to_cpu(src->self_triggers);
	dst->sw_retry_failure = __le32_to_cpu(src->sw_retry_failure);
	dst->illgl_rate_phy_err = __le32_to_cpu(src->illgl_rate_phy_err);
	dst->pdev_cont_xretry = __le32_to_cpu(src->pdev_cont_xretry);
	dst->pdev_tx_timeout = __le32_to_cpu(src->pdev_tx_timeout);
	dst->pdev_resets = __le32_to_cpu(src->pdev_resets);
	dst->phy_underrun = __le32_to_cpu(src->phy_underrun);
	dst->txop_ovf = __le32_to_cpu(src->txop_ovf);
	dst->hw_paused = __le32_to_cpu(src->hw_paused);
	dst->seq_posted = __le32_to_cpu(src->seq_posted);
	dst->seq_failed_queueing =
		__le32_to_cpu(src->seq_failed_queueing);
	dst->seq_completed = __le32_to_cpu(src->seq_completed);
	dst->seq_restarted = __le32_to_cpu(src->seq_restarted);
	dst->mu_seq_posted = __le32_to_cpu(src->mu_seq_posted);
	dst->mpdus_sw_flush = __le32_to_cpu(src->mpdus_sw_flush);
	dst->mpdus_hw_filter = __le32_to_cpu(src->mpdus_hw_filter);
	dst->mpdus_truncated = __le32_to_cpu(src->mpdus_truncated);
	dst->mpdus_ack_failed = __le32_to_cpu(src->mpdus_ack_failed);
	dst->mpdus_hw_filter = __le32_to_cpu(src->mpdus_hw_filter);
	dst->mpdus_expired = __le32_to_cpu(src->mpdus_expired);
}