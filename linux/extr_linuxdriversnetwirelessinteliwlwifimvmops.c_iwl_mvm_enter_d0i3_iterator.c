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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct iwl_mvm_vif {int /*<<< orphan*/  ap_sta_id; } ;
struct iwl_mvm {int dummy; } ;
struct iwl_d0i3_iter_data {int disable_offloading; struct ieee80211_vif* connected_vif; int /*<<< orphan*/  vif_count; int /*<<< orphan*/  ap_sta_id; struct iwl_mvm* mvm; } ;
struct TYPE_2__ {int /*<<< orphan*/  assoc; } ;
struct ieee80211_vif {scalar_t__ type; TYPE_1__ bss_conf; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int CMD_ASYNC ; 
 int CMD_HIGH_PRIO ; 
 int CMD_SEND_IN_IDLE ; 
 int /*<<< orphan*/  IWL_DEBUG_RPM (struct iwl_mvm*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 scalar_t__ iwl_mvm_disallow_offloading (struct iwl_mvm*,struct ieee80211_vif*,struct iwl_d0i3_iter_data*) ; 
 int /*<<< orphan*/  iwl_mvm_send_proto_offload (struct iwl_mvm*,struct ieee80211_vif*,int,int,int) ; 
 int /*<<< orphan*/  iwl_mvm_update_d0i3_power_mode (struct iwl_mvm*,struct ieee80211_vif*,int,int) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 

__attribute__((used)) static void iwl_mvm_enter_d0i3_iterator(void *_data, u8 *mac,
					struct ieee80211_vif *vif)
{
	struct iwl_d0i3_iter_data *data = _data;
	struct iwl_mvm *mvm = data->mvm;
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	u32 flags = CMD_ASYNC | CMD_HIGH_PRIO | CMD_SEND_IN_IDLE;

	IWL_DEBUG_RPM(mvm, "entering D0i3 - vif %pM\n", vif->addr);
	if (vif->type != NL80211_IFTYPE_STATION ||
	    !vif->bss_conf.assoc)
		return;

	/*
	 * in case of pending tx packets or active aggregations,
	 * avoid offloading features in order to prevent reuse of
	 * the same qos seq counters.
	 */
	if (iwl_mvm_disallow_offloading(mvm, vif, data))
		data->disable_offloading = true;

	iwl_mvm_update_d0i3_power_mode(mvm, vif, true, flags);
	iwl_mvm_send_proto_offload(mvm, vif, data->disable_offloading,
				   false, flags);

	/*
	 * on init/association, mvm already configures POWER_TABLE_CMD
	 * and REPLY_MCAST_FILTER_CMD, so currently don't
	 * reconfigure them (we might want to use different
	 * params later on, though).
	 */
	data->ap_sta_id = mvmvif->ap_sta_id;
	data->vif_count++;

	/*
	 * no new commands can be sent at this stage, so it's safe
	 * to save the vif pointer during d0i3 entrance.
	 */
	data->connected_vif = vif;
}