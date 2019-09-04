#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_8__ {int /*<<< orphan*/  bf_enabled; } ;
struct iwl_mvm_vif {int csa_failed; int csa_countdown; int ps_disabled; TYPE_4__ bf_data; int /*<<< orphan*/  csa_target_freq; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; int /*<<< orphan*/  csa_vif; int /*<<< orphan*/  csa_tx_blocked_vif; int /*<<< orphan*/  fwrt; } ;
struct TYPE_7__ {int beacon_int; } ;
struct ieee80211_vif {int type; TYPE_3__ bss_conf; int /*<<< orphan*/  csa_active; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_6__ {TYPE_1__* chan; int /*<<< orphan*/  center_freq1; } ;
struct ieee80211_channel_switch {int count; int /*<<< orphan*/  block_tx; int /*<<< orphan*/  device_timestamp; TYPE_2__ chandef; } ;
struct TYPE_5__ {int /*<<< orphan*/  center_freq; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  FW_DBG_TRIGGER_CHANNEL_SWITCH ; 
 int /*<<< orphan*/  IWL_DEBUG_MAC80211 (struct iwl_mvm*,char*,int /*<<< orphan*/ ) ; 
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 int IWL_MVM_CHANNEL_SWITCH_TIME_CLIENT ; 
#define  NL80211_IFTYPE_AP 129 
#define  NL80211_IFTYPE_STATION 128 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  ieee80211_vif_to_wdev (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_fw_dbg_trigger_simple_stop (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_csa_client_absent (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int iwl_mvm_disable_beacon_filter (struct iwl_mvm*,struct ieee80211_vif*,int /*<<< orphan*/ ) ; 
 int iwl_mvm_power_update_ps (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_schedule_csa_period (struct iwl_mvm*,struct ieee80211_vif*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_teardown_tdls_peers (struct iwl_mvm*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct ieee80211_vif*) ; 
 struct ieee80211_vif* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_mvm_pre_channel_switch(struct ieee80211_hw *hw,
				      struct ieee80211_vif *vif,
				      struct ieee80211_channel_switch *chsw)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	struct ieee80211_vif *csa_vif;
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	u32 apply_time;
	int ret;

	mutex_lock(&mvm->mutex);

	mvmvif->csa_failed = false;

	IWL_DEBUG_MAC80211(mvm, "pre CSA to freq %d\n",
			   chsw->chandef.center_freq1);

	iwl_fw_dbg_trigger_simple_stop(&mvm->fwrt,
				       ieee80211_vif_to_wdev(vif),
				       FW_DBG_TRIGGER_CHANNEL_SWITCH);

	switch (vif->type) {
	case NL80211_IFTYPE_AP:
		csa_vif =
			rcu_dereference_protected(mvm->csa_vif,
						  lockdep_is_held(&mvm->mutex));
		if (WARN_ONCE(csa_vif && csa_vif->csa_active,
			      "Another CSA is already in progress")) {
			ret = -EBUSY;
			goto out_unlock;
		}

		/* we still didn't unblock tx. prevent new CS meanwhile */
		if (rcu_dereference_protected(mvm->csa_tx_blocked_vif,
					      lockdep_is_held(&mvm->mutex))) {
			ret = -EBUSY;
			goto out_unlock;
		}

		rcu_assign_pointer(mvm->csa_vif, vif);

		if (WARN_ONCE(mvmvif->csa_countdown,
			      "Previous CSA countdown didn't complete")) {
			ret = -EBUSY;
			goto out_unlock;
		}

		mvmvif->csa_target_freq = chsw->chandef.chan->center_freq;

		break;
	case NL80211_IFTYPE_STATION:
		/* Schedule the time event to a bit before beacon 1,
		 * to make sure we're in the new channel when the
		 * GO/AP arrives. In case count <= 1 immediately schedule the
		 * TE (this might result with some packet loss or connection
		 * loss).
		 */
		if (chsw->count <= 1)
			apply_time = 0;
		else
			apply_time = chsw->device_timestamp +
				((vif->bss_conf.beacon_int * (chsw->count - 1) -
				  IWL_MVM_CHANNEL_SWITCH_TIME_CLIENT) * 1024);

		if (chsw->block_tx)
			iwl_mvm_csa_client_absent(mvm, vif);

		iwl_mvm_schedule_csa_period(mvm, vif, vif->bss_conf.beacon_int,
					    apply_time);
		if (mvmvif->bf_data.bf_enabled) {
			ret = iwl_mvm_disable_beacon_filter(mvm, vif, 0);
			if (ret)
				goto out_unlock;
		}

		break;
	default:
		break;
	}

	mvmvif->ps_disabled = true;

	ret = iwl_mvm_power_update_ps(mvm);
	if (ret)
		goto out_unlock;

	/* we won't be on this channel any longer */
	iwl_mvm_teardown_tdls_peers(mvm);

out_unlock:
	mutex_unlock(&mvm->mutex);

	return ret;
}