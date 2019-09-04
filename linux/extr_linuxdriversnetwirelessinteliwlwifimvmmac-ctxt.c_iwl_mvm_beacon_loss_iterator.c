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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct iwl_mvm_vif {scalar_t__ id; struct iwl_mvm* mvm; } ;
struct iwl_mvm {int /*<<< orphan*/  fwrt; int /*<<< orphan*/  fw; } ;
struct iwl_missed_beacons_notif {int /*<<< orphan*/  consec_missed_beacons_since_last_rx; int /*<<< orphan*/  consec_missed_beacons; int /*<<< orphan*/  mac_id; } ;
struct iwl_fw_dbg_trigger_tlv {scalar_t__ data; } ;
struct iwl_fw_dbg_trigger_missed_bcon {int /*<<< orphan*/  stop_consec_missed_bcon_since_rx; int /*<<< orphan*/  stop_consec_missed_bcon; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_DBG_TRIGGER_MISSED_BEACONS ; 
 scalar_t__ IWL_MVM_MISSED_BEACONS_THRESHOLD ; 
 int /*<<< orphan*/  ieee80211_beacon_loss (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  ieee80211_vif_to_wdev (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_fw_dbg_collect_trig (int /*<<< orphan*/ *,struct iwl_fw_dbg_trigger_tlv*,int /*<<< orphan*/ *) ; 
 struct iwl_fw_dbg_trigger_tlv* iwl_fw_dbg_get_trigger (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_fw_dbg_trigger_check_stop (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct iwl_fw_dbg_trigger_tlv*) ; 
 int /*<<< orphan*/  iwl_fw_dbg_trigger_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_mvm_beacon_loss_iterator(void *_data, u8 *mac,
					 struct ieee80211_vif *vif)
{
	struct iwl_missed_beacons_notif *missed_beacons = _data;
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_mvm *mvm = mvmvif->mvm;
	struct iwl_fw_dbg_trigger_missed_bcon *bcon_trig;
	struct iwl_fw_dbg_trigger_tlv *trigger;
	u32 stop_trig_missed_bcon, stop_trig_missed_bcon_since_rx;
	u32 rx_missed_bcon, rx_missed_bcon_since_rx;

	if (mvmvif->id != (u16)le32_to_cpu(missed_beacons->mac_id))
		return;

	rx_missed_bcon = le32_to_cpu(missed_beacons->consec_missed_beacons);
	rx_missed_bcon_since_rx =
		le32_to_cpu(missed_beacons->consec_missed_beacons_since_last_rx);
	/*
	 * TODO: the threshold should be adjusted based on latency conditions,
	 * and/or in case of a CS flow on one of the other AP vifs.
	 */
	if (le32_to_cpu(missed_beacons->consec_missed_beacons_since_last_rx) >
	     IWL_MVM_MISSED_BEACONS_THRESHOLD)
		ieee80211_beacon_loss(vif);

	if (!iwl_fw_dbg_trigger_enabled(mvm->fw,
					FW_DBG_TRIGGER_MISSED_BEACONS))
		return;

	trigger = iwl_fw_dbg_get_trigger(mvm->fw,
					 FW_DBG_TRIGGER_MISSED_BEACONS);
	bcon_trig = (void *)trigger->data;
	stop_trig_missed_bcon = le32_to_cpu(bcon_trig->stop_consec_missed_bcon);
	stop_trig_missed_bcon_since_rx =
		le32_to_cpu(bcon_trig->stop_consec_missed_bcon_since_rx);

	/* TODO: implement start trigger */

	if (!iwl_fw_dbg_trigger_check_stop(&mvm->fwrt,
					   ieee80211_vif_to_wdev(vif),
					   trigger))
		return;

	if (rx_missed_bcon_since_rx >= stop_trig_missed_bcon_since_rx ||
	    rx_missed_bcon >= stop_trig_missed_bcon)
		iwl_fw_dbg_collect_trig(&mvm->fwrt, trigger, NULL);
}