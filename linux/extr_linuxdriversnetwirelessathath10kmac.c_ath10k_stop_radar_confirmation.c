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
struct ath10k {int /*<<< orphan*/  radar_confirmation_work; int /*<<< orphan*/  data_lock; int /*<<< orphan*/  radar_conf_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_RADAR_CONFIRMATION_STOPPED ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath10k_stop_radar_confirmation(struct ath10k *ar)
{
	spin_lock_bh(&ar->data_lock);
	ar->radar_conf_state = ATH10K_RADAR_CONFIRMATION_STOPPED;
	spin_unlock_bh(&ar->data_lock);

	cancel_work_sync(&ar->radar_confirmation_work);
}