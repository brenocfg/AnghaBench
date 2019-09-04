#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct iwl_tt_mgmt {scalar_t__ state; } ;
struct iwl_priv {int /*<<< orphan*/  status; struct iwl_tt_mgmt thermal_throttle; } ;
struct TYPE_2__ {int /*<<< orphan*/  ct_kill_waiting_tm; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_TEMP (struct iwl_priv*,char*) ; 
 scalar_t__ IWL_TI_CT_KILL ; 
 int /*<<< orphan*/  STATUS_CT_KILL ; 
 int /*<<< orphan*/  STATUS_EXIT_PENDING ; 
 struct iwl_priv* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_perform_ct_kill_task (struct iwl_priv*,int) ; 
 struct iwl_priv* priv ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ thermal_throttle ; 

__attribute__((used)) static void iwl_tt_ready_for_ct_kill(struct timer_list *t)
{
	struct iwl_priv *priv = from_timer(priv, t,
					   thermal_throttle.ct_kill_waiting_tm);
	struct iwl_tt_mgmt *tt = &priv->thermal_throttle;

	if (test_bit(STATUS_EXIT_PENDING, &priv->status))
		return;

	/* temperature timer expired, ready to go into CT_KILL state */
	if (tt->state != IWL_TI_CT_KILL) {
		IWL_DEBUG_TEMP(priv, "entering CT_KILL state when "
				"temperature timer expired\n");
		tt->state = IWL_TI_CT_KILL;
		set_bit(STATUS_CT_KILL, &priv->status);
		iwl_perform_ct_kill_task(priv, true);
	}
}