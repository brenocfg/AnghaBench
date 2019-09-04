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
struct iwl_mvm_vif {int ap_ibss_active; scalar_t__ ap_assoc_sta_count; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; scalar_t__ p2p_device_vif; TYPE_1__* fw; } ;
struct ieee80211_vif {scalar_t__ type; scalar_t__ p2p; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  IWL_MVM_REF_AP_IBSS ; 
 int /*<<< orphan*/  IWL_MVM_REF_START_AP ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_API_STA_TYPE ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ fw_has_api (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int iwl_mvm_add_mcast_sta (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int iwl_mvm_binding_add_vif (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_binding_remove_vif (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_bt_coex_vif_change (struct iwl_mvm*) ; 
 int iwl_mvm_mac_ctxt_add (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int iwl_mvm_mac_ctxt_beacon_changed (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_mac_ctxt_changed (struct iwl_mvm*,scalar_t__,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_mvm_mac_ctxt_recalc_tsf_id (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_mac_ctxt_remove (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int iwl_mvm_phy_ctx_count (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_power_update_mac (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_ref (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 int iwl_mvm_ref_sync (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_rm_mcast_sta (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int iwl_mvm_send_add_bcast_sta (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_send_rm_bcast_sta (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_teardown_tdls_peers (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_unref (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 int iwl_mvm_update_quotas (struct iwl_mvm*,int,int /*<<< orphan*/ *) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_mvm_start_ap_ibss(struct ieee80211_hw *hw,
				 struct ieee80211_vif *vif)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	int ret;

	/*
	 * iwl_mvm_mac_ctxt_add() might read directly from the device
	 * (the system time), so make sure it is available.
	 */
	ret = iwl_mvm_ref_sync(mvm, IWL_MVM_REF_START_AP);
	if (ret)
		return ret;

	mutex_lock(&mvm->mutex);

	/* Send the beacon template */
	ret = iwl_mvm_mac_ctxt_beacon_changed(mvm, vif);
	if (ret)
		goto out_unlock;

	/*
	 * Re-calculate the tsf id, as the master-slave relations depend on the
	 * beacon interval, which was not known when the AP interface was added.
	 */
	if (vif->type == NL80211_IFTYPE_AP)
		iwl_mvm_mac_ctxt_recalc_tsf_id(mvm, vif);

	mvmvif->ap_assoc_sta_count = 0;

	/* Add the mac context */
	ret = iwl_mvm_mac_ctxt_add(mvm, vif);
	if (ret)
		goto out_unlock;

	/* Perform the binding */
	ret = iwl_mvm_binding_add_vif(mvm, vif);
	if (ret)
		goto out_remove;

	/*
	 * This is not very nice, but the simplest:
	 * For older FWs adding the mcast sta before the bcast station may
	 * cause assert 0x2b00.
	 * This is fixed in later FW so make the order of removal depend on
	 * the TLV
	 */
	if (fw_has_api(&mvm->fw->ucode_capa, IWL_UCODE_TLV_API_STA_TYPE)) {
		ret = iwl_mvm_add_mcast_sta(mvm, vif);
		if (ret)
			goto out_unbind;
		/*
		 * Send the bcast station. At this stage the TBTT and DTIM time
		 * events are added and applied to the scheduler
		 */
		ret = iwl_mvm_send_add_bcast_sta(mvm, vif);
		if (ret) {
			iwl_mvm_rm_mcast_sta(mvm, vif);
			goto out_unbind;
		}
	} else {
		/*
		 * Send the bcast station. At this stage the TBTT and DTIM time
		 * events are added and applied to the scheduler
		 */
		ret = iwl_mvm_send_add_bcast_sta(mvm, vif);
		if (ret)
			goto out_unbind;
		ret = iwl_mvm_add_mcast_sta(mvm, vif);
		if (ret) {
			iwl_mvm_send_rm_bcast_sta(mvm, vif);
			goto out_unbind;
		}
	}

	/* must be set before quota calculations */
	mvmvif->ap_ibss_active = true;

	/* power updated needs to be done before quotas */
	iwl_mvm_power_update_mac(mvm);

	ret = iwl_mvm_update_quotas(mvm, false, NULL);
	if (ret)
		goto out_quota_failed;

	/* Need to update the P2P Device MAC (only GO, IBSS is single vif) */
	if (vif->p2p && mvm->p2p_device_vif)
		iwl_mvm_mac_ctxt_changed(mvm, mvm->p2p_device_vif, false, NULL);

	iwl_mvm_ref(mvm, IWL_MVM_REF_AP_IBSS);

	iwl_mvm_bt_coex_vif_change(mvm);

	/* we don't support TDLS during DCM */
	if (iwl_mvm_phy_ctx_count(mvm) > 1)
		iwl_mvm_teardown_tdls_peers(mvm);

	goto out_unlock;

out_quota_failed:
	iwl_mvm_power_update_mac(mvm);
	mvmvif->ap_ibss_active = false;
	iwl_mvm_send_rm_bcast_sta(mvm, vif);
	iwl_mvm_rm_mcast_sta(mvm, vif);
out_unbind:
	iwl_mvm_binding_remove_vif(mvm, vif);
out_remove:
	iwl_mvm_mac_ctxt_remove(mvm, vif);
out_unlock:
	mutex_unlock(&mvm->mutex);
	iwl_mvm_unref(mvm, IWL_MVM_REF_START_AP);
	return ret;
}