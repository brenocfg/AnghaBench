#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ state; size_t cur_sta_id; int /*<<< orphan*/  dwork; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; TYPE_2__ tdls_cs; int /*<<< orphan*/ * fw_id_to_mac_id; } ;
struct TYPE_3__ {int dtim_period; int beacon_int; } ;
struct ieee80211_vif {TYPE_1__ bss_conf; } ;
struct ieee80211_tdls_ch_sw_params {scalar_t__ action_code; int /*<<< orphan*/  ch_sw_tm_ie; int /*<<< orphan*/  tmpl_skb; int /*<<< orphan*/  switch_timeout; int /*<<< orphan*/  switch_time; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  chandef; struct ieee80211_sta* sta; int /*<<< orphan*/  status; } ;
struct ieee80211_sta {int /*<<< orphan*/  tdls_initiator; int /*<<< orphan*/  addr; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum iwl_tdls_channel_switch_type { ____Placeholder_iwl_tdls_channel_switch_type } iwl_tdls_channel_switch_type ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_TDLS (struct iwl_mvm*,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 size_t IWL_MVM_INVALID_STA ; 
 int /*<<< orphan*/  IWL_MVM_TDLS_SW_IDLE ; 
 scalar_t__ IWL_MVM_TDLS_SW_REQ_SENT ; 
 int TDLS_MOVE_CH ; 
 int TDLS_SEND_CHAN_SW_RESP_AND_MOVE_CH ; 
 scalar_t__ WLAN_TDLS_CHANNEL_SWITCH_REQUEST ; 
 scalar_t__ WLAN_TDLS_CHANNEL_SWITCH_RESPONSE ; 
 int /*<<< orphan*/  iwl_mvm_tdls_config_channel_switch (struct iwl_mvm*,struct ieee80211_vif*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_tdls_update_cs_state (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ieee80211_sta* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_wq ; 

void
iwl_mvm_tdls_recv_channel_switch(struct ieee80211_hw *hw,
				 struct ieee80211_vif *vif,
				 struct ieee80211_tdls_ch_sw_params *params)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	enum iwl_tdls_channel_switch_type type;
	unsigned int delay;
	const char *action_str =
		params->action_code == WLAN_TDLS_CHANNEL_SWITCH_REQUEST ?
		"REQ" : "RESP";

	mutex_lock(&mvm->mutex);

	IWL_DEBUG_TDLS(mvm,
		       "Received TDLS ch switch action %s from %pM status %d\n",
		       action_str, params->sta->addr, params->status);

	/*
	 * we got a non-zero status from a peer we were switching to - move to
	 * the idle state and retry again later
	 */
	if (params->action_code == WLAN_TDLS_CHANNEL_SWITCH_RESPONSE &&
	    params->status != 0 &&
	    mvm->tdls_cs.state == IWL_MVM_TDLS_SW_REQ_SENT &&
	    mvm->tdls_cs.cur_sta_id != IWL_MVM_INVALID_STA) {
		struct ieee80211_sta *cur_sta;

		/* make sure it's the same peer */
		cur_sta = rcu_dereference_protected(
				mvm->fw_id_to_mac_id[mvm->tdls_cs.cur_sta_id],
				lockdep_is_held(&mvm->mutex));
		if (cur_sta == params->sta) {
			iwl_mvm_tdls_update_cs_state(mvm,
						     IWL_MVM_TDLS_SW_IDLE);
			goto retry;
		}
	}

	type = (params->action_code == WLAN_TDLS_CHANNEL_SWITCH_REQUEST) ?
	       TDLS_SEND_CHAN_SW_RESP_AND_MOVE_CH : TDLS_MOVE_CH;

	iwl_mvm_tdls_config_channel_switch(mvm, vif, type, params->sta->addr,
					   params->sta->tdls_initiator, 0,
					   params->chandef, params->timestamp,
					   params->switch_time,
					   params->switch_timeout,
					   params->tmpl_skb,
					   params->ch_sw_tm_ie);

retry:
	/* register a timeout in case we don't succeed in switching */
	delay = vif->bss_conf.dtim_period * vif->bss_conf.beacon_int *
		1024 / 1000;
	mod_delayed_work(system_wq, &mvm->tdls_cs.dwork,
			 msecs_to_jiffies(delay));
	mutex_unlock(&mvm->mutex);
}