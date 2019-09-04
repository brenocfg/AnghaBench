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
struct iwl_wowlan_config_cmd {int flags; int /*<<< orphan*/  offloading_tid; int /*<<< orphan*/  is_11n_connection; } ;
struct iwl_mvm_sta {int dummy; } ;
struct iwl_mvm {int /*<<< orphan*/ * fw_id_to_mac_id; } ;
struct iwl_d0i3_iter_data {size_t ap_sta_id; int /*<<< orphan*/  offloading_tid; } ;
struct TYPE_2__ {int /*<<< orphan*/  ht_supported; } ;
struct ieee80211_sta {TYPE_1__ ht_cap; } ;

/* Variables and functions */
 int ENABLE_DHCP_FILTERING ; 
 int ENABLE_L3_FILTERING ; 
 int ENABLE_NBNS_FILTERING ; 
 int ENABLE_STORE_BEACON ; 
 scalar_t__ IS_ERR_OR_NULL (struct ieee80211_sta*) ; 
 size_t IWL_MVM_INVALID_STA ; 
 int /*<<< orphan*/  iwl_mvm_set_wowlan_qos_seq (struct iwl_mvm_sta*,struct iwl_wowlan_config_cmd*) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 
 struct ieee80211_sta* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static void iwl_mvm_set_wowlan_data(struct iwl_mvm *mvm,
				    struct iwl_wowlan_config_cmd *cmd,
				    struct iwl_d0i3_iter_data *iter_data)
{
	struct ieee80211_sta *ap_sta;
	struct iwl_mvm_sta *mvm_ap_sta;

	if (iter_data->ap_sta_id == IWL_MVM_INVALID_STA)
		return;

	rcu_read_lock();

	ap_sta = rcu_dereference(mvm->fw_id_to_mac_id[iter_data->ap_sta_id]);
	if (IS_ERR_OR_NULL(ap_sta))
		goto out;

	mvm_ap_sta = iwl_mvm_sta_from_mac80211(ap_sta);
	cmd->is_11n_connection = ap_sta->ht_cap.ht_supported;
	cmd->offloading_tid = iter_data->offloading_tid;
	cmd->flags = ENABLE_L3_FILTERING | ENABLE_NBNS_FILTERING |
		ENABLE_DHCP_FILTERING | ENABLE_STORE_BEACON;
	/*
	 * The d0i3 uCode takes care of the nonqos counters,
	 * so configure only the qos seq ones.
	 */
	iwl_mvm_set_wowlan_qos_seq(mvm_ap_sta, cmd);
out:
	rcu_read_unlock();
}