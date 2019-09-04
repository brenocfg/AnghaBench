#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * firmware; scalar_t__ codeswap_len; scalar_t__ codeswap_data; } ;
struct TYPE_4__ {TYPE_3__ fw_file; } ;
struct TYPE_5__ {int utf_monitor; TYPE_1__ utf_mode_fw; } ;
struct ath10k {int /*<<< orphan*/  state; TYPE_2__ testmode; int /*<<< orphan*/  data_lock; int /*<<< orphan*/  conf_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_STATE_OFF ; 
 int /*<<< orphan*/  ath10k_core_stop (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_hif_power_down (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_swap_code_seg_release (struct ath10k*,TYPE_3__*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __ath10k_tm_cmd_utf_stop(struct ath10k *ar)
{
	lockdep_assert_held(&ar->conf_mutex);

	ath10k_core_stop(ar);
	ath10k_hif_power_down(ar);

	spin_lock_bh(&ar->data_lock);

	ar->testmode.utf_monitor = false;

	spin_unlock_bh(&ar->data_lock);

	if (ar->testmode.utf_mode_fw.fw_file.codeswap_data &&
	    ar->testmode.utf_mode_fw.fw_file.codeswap_len)
		ath10k_swap_code_seg_release(ar,
					     &ar->testmode.utf_mode_fw.fw_file);

	release_firmware(ar->testmode.utf_mode_fw.fw_file.firmware);
	ar->testmode.utf_mode_fw.fw_file.firmware = NULL;

	ar->state = ATH10K_STATE_OFF;
}