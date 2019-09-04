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
struct iwl_mvm_vif {struct iwl_mvm_phy_ctxt* phy_ctxt; } ;
struct iwl_mvm_sta {int /*<<< orphan*/  vif; } ;
struct iwl_mvm_phy_ctxt {int /*<<< orphan*/  id; } ;
struct TYPE_2__ {int ttc_status; int /*<<< orphan*/  bt_activity_grading; } ;
struct iwl_mvm {TYPE_1__ last_bt_notif; } ;
struct ieee80211_sta {int dummy; } ;
typedef  enum iwl_bt_coex_lut_type { ____Placeholder_iwl_bt_coex_lut_type } iwl_bt_coex_lut_type ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int BT_COEX_LOOSE_LUT ; 
 scalar_t__ BT_HIGH_TRAFFIC ; 
 int iwl_get_coex_type (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

bool iwl_mvm_bt_coex_is_mimo_allowed(struct iwl_mvm *mvm,
				     struct ieee80211_sta *sta)
{
	struct iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(mvmsta->vif);
	struct iwl_mvm_phy_ctxt *phy_ctxt = mvmvif->phy_ctxt;
	enum iwl_bt_coex_lut_type lut_type;

	if (mvm->last_bt_notif.ttc_status & BIT(phy_ctxt->id))
		return true;

	if (le32_to_cpu(mvm->last_bt_notif.bt_activity_grading) <
	    BT_HIGH_TRAFFIC)
		return true;

	/*
	 * In Tight / TxTxDis, BT can't Rx while we Tx, so use both antennas
	 * since BT is already killed.
	 * In Loose, BT can Rx while we Tx, so forbid MIMO to let BT Rx while
	 * we Tx.
	 * When we are in 5GHz, we'll get BT_COEX_INVALID_LUT allowing MIMO.
	 */
	lut_type = iwl_get_coex_type(mvm, mvmsta->vif);
	return lut_type != BT_COEX_LOOSE_LUT;
}