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
struct iwl_priv {int /*<<< orphan*/  ucode_trace; int /*<<< orphan*/  statistics_periodic; int /*<<< orphan*/  bt_runtime_config; int /*<<< orphan*/  bt_full_concurrency; int /*<<< orphan*/  beacon_update; int /*<<< orphan*/  run_time_calib_work; TYPE_1__* lib; } ;
struct TYPE_2__ {scalar_t__ bt_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_cancel_scan_deferred_work (struct iwl_priv*) ; 
 int /*<<< orphan*/  iwlagn_bt_cancel_deferred_work (struct iwl_priv*) ; 

void iwl_cancel_deferred_work(struct iwl_priv *priv)
{
	if (priv->lib->bt_params)
		iwlagn_bt_cancel_deferred_work(priv);

	cancel_work_sync(&priv->run_time_calib_work);
	cancel_work_sync(&priv->beacon_update);

	iwl_cancel_scan_deferred_work(priv);

	cancel_work_sync(&priv->bt_full_concurrency);
	cancel_work_sync(&priv->bt_runtime_config);

	del_timer_sync(&priv->statistics_periodic);
	del_timer_sync(&priv->ucode_trace);
}