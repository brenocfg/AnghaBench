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
struct il_rxon_cmd {int /*<<< orphan*/  filter_flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  filter_flags; } ;
struct TYPE_4__ {scalar_t__ is_valid; } ;
struct il_priv {int /*<<< orphan*/  restart; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  wait_command_queue; int /*<<< orphan*/  status; TYPE_3__* ops; TYPE_2__ staging; int /*<<< orphan*/  active; int /*<<< orphan*/  active_rate; int /*<<< orphan*/  hw; TYPE_1__ card_alive; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* set_rxon_chain ) (struct il_priv*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  D_INFO (char*) ; 
 int /*<<< orphan*/  IL_WARN (char*,int) ; 
 int /*<<< orphan*/  RATES_MASK ; 
 int /*<<< orphan*/  RXON_FILTER_ASSOC_MSK ; 
 int /*<<< orphan*/  S_ALIVE ; 
 int /*<<< orphan*/  S_READY ; 
 scalar_t__ UCODE_VALID_OK ; 
 int /*<<< orphan*/  ieee80211_wake_queues (int /*<<< orphan*/ ) ; 
 int il4965_alive_notify (struct il_priv*) ; 
 int /*<<< orphan*/  il4965_reset_run_time_calib (struct il_priv*) ; 
 int /*<<< orphan*/  il4965_rf_kill_ct_config (struct il_priv*) ; 
 scalar_t__ il4965_verify_ucode (struct il_priv*) ; 
 int /*<<< orphan*/  il_commit_rxon (struct il_priv*) ; 
 int /*<<< orphan*/  il_connection_init_rx_config (struct il_priv*) ; 
 scalar_t__ il_is_associated (struct il_priv*) ; 
 scalar_t__ il_is_rfkill (struct il_priv*) ; 
 int /*<<< orphan*/  il_power_update_mode (struct il_priv*,int) ; 
 int /*<<< orphan*/  il_send_bt_config (struct il_priv*) ; 
 int /*<<< orphan*/  il_setup_watchdog (struct il_priv*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct il_priv*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
il4965_alive_start(struct il_priv *il)
{
	int ret = 0;

	D_INFO("Runtime Alive received.\n");

	if (il->card_alive.is_valid != UCODE_VALID_OK) {
		/* We had an error bringing up the hardware, so take it
		 * all the way back down so we can try again */
		D_INFO("Alive failed.\n");
		goto restart;
	}

	/* Initialize uCode has loaded Runtime uCode ... verify inst image.
	 * This is a paranoid check, because we would not have gotten the
	 * "runtime" alive if code weren't properly loaded.  */
	if (il4965_verify_ucode(il)) {
		/* Runtime instruction load was bad;
		 * take it all the way back down so we can try again */
		D_INFO("Bad runtime uCode load.\n");
		goto restart;
	}

	ret = il4965_alive_notify(il);
	if (ret) {
		IL_WARN("Could not complete ALIVE transition [ntf]: %d\n", ret);
		goto restart;
	}

	/* After the ALIVE response, we can send host commands to the uCode */
	set_bit(S_ALIVE, &il->status);

	/* Enable watchdog to monitor the driver tx queues */
	il_setup_watchdog(il);

	if (il_is_rfkill(il))
		return;

	ieee80211_wake_queues(il->hw);

	il->active_rate = RATES_MASK;

	il_power_update_mode(il, true);
	D_INFO("Updated power mode\n");

	if (il_is_associated(il)) {
		struct il_rxon_cmd *active_rxon =
		    (struct il_rxon_cmd *)&il->active;
		/* apply any changes in staging */
		il->staging.filter_flags |= RXON_FILTER_ASSOC_MSK;
		active_rxon->filter_flags &= ~RXON_FILTER_ASSOC_MSK;
	} else {
		/* Initialize our rx_config data */
		il_connection_init_rx_config(il);

		if (il->ops->set_rxon_chain)
			il->ops->set_rxon_chain(il);
	}

	/* Configure bluetooth coexistence if enabled */
	il_send_bt_config(il);

	il4965_reset_run_time_calib(il);

	set_bit(S_READY, &il->status);

	/* Configure the adapter for unassociated operation */
	il_commit_rxon(il);

	/* At this point, the NIC is initialized and operational */
	il4965_rf_kill_ct_config(il);

	D_INFO("ALIVE processing complete.\n");
	wake_up(&il->wait_command_queue);

	return;

restart:
	queue_work(il->workqueue, &il->restart);
}