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
struct iwl_mvm_vif {scalar_t__ ap_sta_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  bt_activity_grading; } ;
struct iwl_mvm {scalar_t__ bt_force_ant_mode; TYPE_3__* cfg; TYPE_1__ last_bt_notif; int /*<<< orphan*/  mutex; } ;
struct TYPE_5__ {int /*<<< orphan*/  bssid; } ;
struct ieee80211_vif {TYPE_2__ bss_conf; } ;
typedef  enum ieee80211_rssi_event_data { ____Placeholder_ieee80211_rssi_event_data } ieee80211_rssi_event_data ;
struct TYPE_6__ {scalar_t__ bt_shared_single_ant; } ;

/* Variables and functions */
 scalar_t__ BT_COEX_LOOSE_LUT ; 
 scalar_t__ BT_FORCE_ANT_DIS ; 
 scalar_t__ BT_OFF ; 
 int /*<<< orphan*/  IWL_DEBUG_COEX (struct iwl_mvm*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 scalar_t__ IWL_MVM_INVALID_STA ; 
 int RSSI_EVENT_HIGH ; 
 int RSSI_EVENT_LOW ; 
 scalar_t__ iwl_get_coex_type (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int iwl_mvm_bt_coex_reduced_txp (struct iwl_mvm*,scalar_t__,int) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void iwl_mvm_bt_rssi_event(struct iwl_mvm *mvm, struct ieee80211_vif *vif,
			   enum ieee80211_rssi_event_data rssi_event)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	int ret;

	lockdep_assert_held(&mvm->mutex);

	/* Ignore updates if we are in force mode */
	if (unlikely(mvm->bt_force_ant_mode != BT_FORCE_ANT_DIS))
		return;

	/*
	 * Rssi update while not associated - can happen since the statistics
	 * are handled asynchronously
	 */
	if (mvmvif->ap_sta_id == IWL_MVM_INVALID_STA)
		return;

	/* No BT - reports should be disabled */
	if (le32_to_cpu(mvm->last_bt_notif.bt_activity_grading) == BT_OFF)
		return;

	IWL_DEBUG_COEX(mvm, "RSSI for %pM is now %s\n", vif->bss_conf.bssid,
		       rssi_event == RSSI_EVENT_HIGH ? "HIGH" : "LOW");

	/*
	 * Check if rssi is good enough for reduced Tx power, but not in loose
	 * scheme.
	 */
	if (rssi_event == RSSI_EVENT_LOW || mvm->cfg->bt_shared_single_ant ||
	    iwl_get_coex_type(mvm, vif) == BT_COEX_LOOSE_LUT)
		ret = iwl_mvm_bt_coex_reduced_txp(mvm, mvmvif->ap_sta_id,
						  false);
	else
		ret = iwl_mvm_bt_coex_reduced_txp(mvm, mvmvif->ap_sta_id, true);

	if (ret)
		IWL_ERR(mvm, "couldn't send BT_CONFIG HCMD upon RSSI event\n");
}