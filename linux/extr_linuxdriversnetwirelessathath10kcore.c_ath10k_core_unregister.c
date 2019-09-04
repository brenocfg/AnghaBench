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
struct ath10k {int /*<<< orphan*/  dev_flags; int /*<<< orphan*/  register_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_FLAG_CORE_REGISTERED ; 
 int /*<<< orphan*/  ath10k_core_free_board_files (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_core_free_firmware_files (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_debug_unregister (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_mac_unregister (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_spectral_destroy (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_testmode_destroy (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_thermal_unregister (struct ath10k*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ath10k_core_unregister(struct ath10k *ar)
{
	cancel_work_sync(&ar->register_work);

	if (!test_bit(ATH10K_FLAG_CORE_REGISTERED, &ar->dev_flags))
		return;

	ath10k_thermal_unregister(ar);
	/* Stop spectral before unregistering from mac80211 to remove the
	 * relayfs debugfs file cleanly. Otherwise the parent debugfs tree
	 * would be already be free'd recursively, leading to a double free.
	 */
	ath10k_spectral_destroy(ar);

	/* We must unregister from mac80211 before we stop HTC and HIF.
	 * Otherwise we will fail to submit commands to FW and mac80211 will be
	 * unhappy about callback failures.
	 */
	ath10k_mac_unregister(ar);

	ath10k_testmode_destroy(ar);

	ath10k_core_free_firmware_files(ar);
	ath10k_core_free_board_files(ar);

	ath10k_debug_unregister(ar);
}