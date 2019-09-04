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
struct iwl_tt_mgmt {int /*<<< orphan*/ * transaction; int /*<<< orphan*/ * restriction; scalar_t__ advanced_tt; int /*<<< orphan*/  ct_kill_waiting_tm; int /*<<< orphan*/  ct_kill_exit_tm; } ;
struct iwl_priv {struct iwl_tt_mgmt thermal_throttle; int /*<<< orphan*/  ct_exit; int /*<<< orphan*/  ct_enter; int /*<<< orphan*/  tt_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void iwl_tt_exit(struct iwl_priv *priv)
{
	struct iwl_tt_mgmt *tt = &priv->thermal_throttle;

	/* stop ct_kill_exit_tm timer if activated */
	del_timer_sync(&priv->thermal_throttle.ct_kill_exit_tm);
	/* stop ct_kill_waiting_tm timer if activated */
	del_timer_sync(&priv->thermal_throttle.ct_kill_waiting_tm);
	cancel_work_sync(&priv->tt_work);
	cancel_work_sync(&priv->ct_enter);
	cancel_work_sync(&priv->ct_exit);

	if (priv->thermal_throttle.advanced_tt) {
		/* free advance thermal throttling memory */
		kfree(tt->restriction);
		tt->restriction = NULL;
		kfree(tt->transaction);
		tt->transaction = NULL;
	}
}