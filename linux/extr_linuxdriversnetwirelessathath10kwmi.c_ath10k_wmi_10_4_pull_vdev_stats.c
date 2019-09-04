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
struct wmi_vdev_stats_extd {int /*<<< orphan*/  rx_iftmr_dup_cnt; int /*<<< orphan*/  rx_iftmr_cnt; int /*<<< orphan*/  rx_ftmr_dup_cnt; int /*<<< orphan*/  rx_ftmr_cnt; int /*<<< orphan*/  tx_ftm_fail; int /*<<< orphan*/  tx_ftm_suc_retry; int /*<<< orphan*/  tx_ftm_suc; int /*<<< orphan*/  mpdu_fail_retry; int /*<<< orphan*/  mpdu_suc_multitry; int /*<<< orphan*/  mpdu_suc_retry; int /*<<< orphan*/  mpdu_sw_requeued; int /*<<< orphan*/  ppdu_nonaggr_cnt; int /*<<< orphan*/  mpdu_queued; int /*<<< orphan*/  ppdu_noack; int /*<<< orphan*/  ppdu_aggr_cnt; int /*<<< orphan*/  vdev_id; } ;
struct ath10k_fw_stats_vdev_extd {void* rx_iftmr_dup_cnt; void* rx_iftmr_cnt; void* rx_ftmr_dup_cnt; void* rx_ftmr_cnt; void* tx_ftm_fail; void* tx_ftm_suc_retry; void* tx_ftm_suc; void* mpdu_fail_retry; void* mpdu_suc_multitry; void* mpdu_suc_retry; void* mpdu_sw_requeued; void* ppdu_nonaggr_cnt; void* mpdu_queued; void* ppdu_noack; void* ppdu_aggr_cnt; void* vdev_id; } ;

/* Variables and functions */
 void* __le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ath10k_wmi_10_4_pull_vdev_stats(const struct wmi_vdev_stats_extd *src,
				struct ath10k_fw_stats_vdev_extd *dst)
{
	dst->vdev_id = __le32_to_cpu(src->vdev_id);
	dst->ppdu_aggr_cnt = __le32_to_cpu(src->ppdu_aggr_cnt);
	dst->ppdu_noack = __le32_to_cpu(src->ppdu_noack);
	dst->mpdu_queued = __le32_to_cpu(src->mpdu_queued);
	dst->ppdu_nonaggr_cnt = __le32_to_cpu(src->ppdu_nonaggr_cnt);
	dst->mpdu_sw_requeued = __le32_to_cpu(src->mpdu_sw_requeued);
	dst->mpdu_suc_retry = __le32_to_cpu(src->mpdu_suc_retry);
	dst->mpdu_suc_multitry = __le32_to_cpu(src->mpdu_suc_multitry);
	dst->mpdu_fail_retry = __le32_to_cpu(src->mpdu_fail_retry);
	dst->tx_ftm_suc = __le32_to_cpu(src->tx_ftm_suc);
	dst->tx_ftm_suc_retry = __le32_to_cpu(src->tx_ftm_suc_retry);
	dst->tx_ftm_fail = __le32_to_cpu(src->tx_ftm_fail);
	dst->rx_ftmr_cnt = __le32_to_cpu(src->rx_ftmr_cnt);
	dst->rx_ftmr_dup_cnt = __le32_to_cpu(src->rx_ftmr_dup_cnt);
	dst->rx_iftmr_cnt = __le32_to_cpu(src->rx_iftmr_cnt);
	dst->rx_iftmr_dup_cnt = __le32_to_cpu(src->rx_iftmr_dup_cnt);
}