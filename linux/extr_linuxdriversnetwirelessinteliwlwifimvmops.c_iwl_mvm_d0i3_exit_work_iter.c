#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct iwl_mvm_vif {scalar_t__ ap_sta_id; } ;
struct iwl_mvm_d0i3_exit_work_iter_data {int wakeup_reasons; int /*<<< orphan*/  status; TYPE_2__* mvm; } ;
struct TYPE_4__ {int /*<<< orphan*/  assoc; } ;
struct ieee80211_vif {scalar_t__ type; TYPE_1__ bss_conf; } ;
struct TYPE_5__ {scalar_t__ d0i3_ap_sta_id; } ;

/* Variables and functions */
 int IWL_WOWLAN_WAKEUP_BY_DISCONNECTION_ON_DEAUTH ; 
 int IWL_WOWLAN_WAKEUP_BY_DISCONNECTION_ON_MISSED_BEACON ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  ieee80211_beacon_loss (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_connection_loss (TYPE_2__*,struct ieee80211_vif*,char*) ; 
 int /*<<< orphan*/  iwl_mvm_d0i3_update_keys (TYPE_2__*,struct ieee80211_vif*,int /*<<< orphan*/ ) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 

__attribute__((used)) static void iwl_mvm_d0i3_exit_work_iter(void *_data, u8 *mac,
					struct ieee80211_vif *vif)
{
	struct iwl_mvm_d0i3_exit_work_iter_data *data = _data;
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	u32 reasons = data->wakeup_reasons;

	/* consider only the relevant station interface */
	if (vif->type != NL80211_IFTYPE_STATION || !vif->bss_conf.assoc ||
	    data->mvm->d0i3_ap_sta_id != mvmvif->ap_sta_id)
		return;

	if (reasons & IWL_WOWLAN_WAKEUP_BY_DISCONNECTION_ON_DEAUTH)
		iwl_mvm_connection_loss(data->mvm, vif, "D0i3");
	else if (reasons & IWL_WOWLAN_WAKEUP_BY_DISCONNECTION_ON_MISSED_BEACON)
		ieee80211_beacon_loss(vif);
	else
		iwl_mvm_d0i3_update_keys(data->mvm, vif, data->status);
}