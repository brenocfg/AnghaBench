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
struct ath10k {scalar_t__ state; int /*<<< orphan*/  htt; int /*<<< orphan*/  conf_mutex; } ;

/* Variables and functions */
 scalar_t__ ATH10K_STATE_RESTARTING ; 
 scalar_t__ ATH10K_STATE_UTF ; 
 int /*<<< orphan*/  WMI_PDEV_SUSPEND_AND_DISABLE_INTR ; 
 int /*<<< orphan*/  ath10k_debug_stop (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_hif_stop (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_htt_rx_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath10k_htt_tx_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath10k_wait_for_suspend (struct ath10k*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_wmi_detach (struct ath10k*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void ath10k_core_stop(struct ath10k *ar)
{
	lockdep_assert_held(&ar->conf_mutex);
	ath10k_debug_stop(ar);

	/* try to suspend target */
	if (ar->state != ATH10K_STATE_RESTARTING &&
	    ar->state != ATH10K_STATE_UTF)
		ath10k_wait_for_suspend(ar, WMI_PDEV_SUSPEND_AND_DISABLE_INTR);

	ath10k_hif_stop(ar);
	ath10k_htt_tx_stop(&ar->htt);
	ath10k_htt_rx_free(&ar->htt);
	ath10k_wmi_detach(ar);
}