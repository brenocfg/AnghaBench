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
struct ath10k_htt {int num_pending_tx; int max_num_pending_tx; int /*<<< orphan*/  ar; int /*<<< orphan*/  tx_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_TX_PAUSE_Q_FULL ; 
 int /*<<< orphan*/  ath10k_mac_tx_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void ath10k_htt_tx_dec_pending(struct ath10k_htt *htt)
{
	lockdep_assert_held(&htt->tx_lock);

	htt->num_pending_tx--;
	if (htt->num_pending_tx == htt->max_num_pending_tx - 1)
		ath10k_mac_tx_unlock(htt->ar, ATH10K_TX_PAUSE_Q_FULL);
}