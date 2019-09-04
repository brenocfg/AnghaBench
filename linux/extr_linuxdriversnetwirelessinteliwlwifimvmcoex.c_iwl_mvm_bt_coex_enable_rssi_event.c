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
struct TYPE_2__ {int last_bt_coex_event; int /*<<< orphan*/  bt_coex_min_thold; int /*<<< orphan*/  bt_coex_max_thold; } ;
struct iwl_mvm_vif {TYPE_1__ bf_data; } ;
struct iwl_mvm {int dummy; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_MVM_BT_COEX_DIS_RED_TXP_THRESH ; 
 int /*<<< orphan*/  IWL_MVM_BT_COEX_EN_RED_TXP_THRESH ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 

__attribute__((used)) static inline
void iwl_mvm_bt_coex_enable_rssi_event(struct iwl_mvm *mvm,
				       struct ieee80211_vif *vif,
				       bool enable, int rssi)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);

	mvmvif->bf_data.last_bt_coex_event = rssi;
	mvmvif->bf_data.bt_coex_max_thold =
		enable ? -IWL_MVM_BT_COEX_EN_RED_TXP_THRESH : 0;
	mvmvif->bf_data.bt_coex_min_thold =
		enable ? -IWL_MVM_BT_COEX_DIS_RED_TXP_THRESH : 0;
}