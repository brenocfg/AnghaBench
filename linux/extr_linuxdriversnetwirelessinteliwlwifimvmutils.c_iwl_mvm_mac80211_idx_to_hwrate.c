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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/ * fw_rate_idx_to_plcp ; 

u8 iwl_mvm_mac80211_idx_to_hwrate(int rate_idx)
{
	/* Get PLCP rate for tx_cmd->rate_n_flags */
	return fw_rate_idx_to_plcp[rate_idx];
}