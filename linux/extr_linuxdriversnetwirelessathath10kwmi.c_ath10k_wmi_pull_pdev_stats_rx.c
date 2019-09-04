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
struct wmi_pdev_stats_rx {int /*<<< orphan*/  mpdu_errs; int /*<<< orphan*/  phy_err_drop; int /*<<< orphan*/  phy_errs; int /*<<< orphan*/  oversize_amsdu; int /*<<< orphan*/  loc_mpdus; int /*<<< orphan*/  loc_msdus; int /*<<< orphan*/  htt_mpdus; int /*<<< orphan*/  htt_msdus; int /*<<< orphan*/  r3_frags; int /*<<< orphan*/  r2_frags; int /*<<< orphan*/  r1_frags; int /*<<< orphan*/  r0_frags; int /*<<< orphan*/  status_rcvd; int /*<<< orphan*/  mid_ppdu_route_change; } ;
struct ath10k_fw_stats_pdev {void* mpdu_errs; void* phy_err_drop; void* phy_errs; void* oversize_amsdu; void* loc_mpdus; void* loc_msdus; void* htt_mpdus; void* htt_msdus; void* r3_frags; void* r2_frags; void* r1_frags; void* r0_frags; void* status_rcvd; void* mid_ppdu_route_change; } ;

/* Variables and functions */
 void* __le32_to_cpu (int /*<<< orphan*/ ) ; 

void ath10k_wmi_pull_pdev_stats_rx(const struct wmi_pdev_stats_rx *src,
				   struct ath10k_fw_stats_pdev *dst)
{
	dst->mid_ppdu_route_change = __le32_to_cpu(src->mid_ppdu_route_change);
	dst->status_rcvd = __le32_to_cpu(src->status_rcvd);
	dst->r0_frags = __le32_to_cpu(src->r0_frags);
	dst->r1_frags = __le32_to_cpu(src->r1_frags);
	dst->r2_frags = __le32_to_cpu(src->r2_frags);
	dst->r3_frags = __le32_to_cpu(src->r3_frags);
	dst->htt_msdus = __le32_to_cpu(src->htt_msdus);
	dst->htt_mpdus = __le32_to_cpu(src->htt_mpdus);
	dst->loc_msdus = __le32_to_cpu(src->loc_msdus);
	dst->loc_mpdus = __le32_to_cpu(src->loc_mpdus);
	dst->oversize_amsdu = __le32_to_cpu(src->oversize_amsdu);
	dst->phy_errs = __le32_to_cpu(src->phy_errs);
	dst->phy_err_drop = __le32_to_cpu(src->phy_err_drop);
	dst->mpdu_errs = __le32_to_cpu(src->mpdu_errs);
}