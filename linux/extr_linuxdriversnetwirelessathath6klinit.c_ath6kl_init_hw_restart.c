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
struct ath6kl {int /*<<< orphan*/  flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_RECOVERY ; 
 int /*<<< orphan*/  WMI_READY ; 
 scalar_t__ __ath6kl_init_hw_start (struct ath6kl*) ; 
 scalar_t__ __ath6kl_init_hw_stop (struct ath6kl*) ; 
 int /*<<< orphan*/  ath6kl_cfg80211_stop_all (struct ath6kl*) ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ath6kl_init_hw_restart(struct ath6kl *ar)
{
	clear_bit(WMI_READY, &ar->flag);

	ath6kl_cfg80211_stop_all(ar);

	if (__ath6kl_init_hw_stop(ar)) {
		ath6kl_dbg(ATH6KL_DBG_RECOVERY, "Failed to stop during fw error recovery\n");
		return;
	}

	if (__ath6kl_init_hw_start(ar)) {
		ath6kl_dbg(ATH6KL_DBG_RECOVERY, "Failed to restart during fw error recovery\n");
		return;
	}
}