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
struct ath10k_htt {scalar_t__ num_pending_tx; scalar_t__ max_num_pending_tx; int /*<<< orphan*/  ar; int /*<<< orphan*/  tx_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_TX_PAUSE_Q_FULL ; 
 int EBUSY ; 
 int /*<<< orphan*/  ath10k_mac_tx_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

int ath10k_htt_tx_inc_pending(struct ath10k_htt *htt)
{
	lockdep_assert_held(&htt->tx_lock);

	if (htt->num_pending_tx >= htt->max_num_pending_tx)
		return -EBUSY;

	htt->num_pending_tx++;
	if (htt->num_pending_tx == htt->max_num_pending_tx)
		ath10k_mac_tx_lock(htt->ar, ATH10K_TX_PAUSE_Q_FULL);

	return 0;
}