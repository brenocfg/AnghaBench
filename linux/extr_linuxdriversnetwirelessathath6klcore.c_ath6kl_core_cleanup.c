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
struct ath6kl {int /*<<< orphan*/  fw_testscript; int /*<<< orphan*/  fw_patch; int /*<<< orphan*/  fw; int /*<<< orphan*/  fw_otp; int /*<<< orphan*/  fw_board; scalar_t__ htc_target; int /*<<< orphan*/  ath6kl_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath6kl_bmi_cleanup (struct ath6kl*) ; 
 int /*<<< orphan*/  ath6kl_cfg80211_cleanup (struct ath6kl*) ; 
 int /*<<< orphan*/  ath6kl_cleanup_amsdu_rxbufs (struct ath6kl*) ; 
 int /*<<< orphan*/  ath6kl_cookie_cleanup (struct ath6kl*) ; 
 int /*<<< orphan*/  ath6kl_debug_cleanup (struct ath6kl*) ; 
 int /*<<< orphan*/  ath6kl_hif_power_off (struct ath6kl*) ; 
 int /*<<< orphan*/  ath6kl_htc_cleanup (scalar_t__) ; 
 int /*<<< orphan*/  ath6kl_recovery_cleanup (struct ath6kl*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

void ath6kl_core_cleanup(struct ath6kl *ar)
{
	ath6kl_hif_power_off(ar);

	ath6kl_recovery_cleanup(ar);

	destroy_workqueue(ar->ath6kl_wq);

	if (ar->htc_target)
		ath6kl_htc_cleanup(ar->htc_target);

	ath6kl_cookie_cleanup(ar);

	ath6kl_cleanup_amsdu_rxbufs(ar);

	ath6kl_bmi_cleanup(ar);

	ath6kl_debug_cleanup(ar);

	kfree(ar->fw_board);
	kfree(ar->fw_otp);
	vfree(ar->fw);
	kfree(ar->fw_patch);
	kfree(ar->fw_testscript);

	ath6kl_cfg80211_cleanup(ar);
}