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
struct iwl_mvm_vif {int /*<<< orphan*/  phy_ctxt; } ;
struct iwl_mvm {int dummy; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int iwl_mvm_binding_update (struct iwl_mvm*,struct ieee80211_vif*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ iwl_mvm_sf_update (struct iwl_mvm*,struct ieee80211_vif*,int) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 

int iwl_mvm_binding_remove_vif(struct iwl_mvm *mvm, struct ieee80211_vif *vif)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	int ret;

	if (WARN_ON_ONCE(!mvmvif->phy_ctxt))
		return -EINVAL;

	ret = iwl_mvm_binding_update(mvm, vif, mvmvif->phy_ctxt, false);

	if (!ret)
		if (iwl_mvm_sf_update(mvm, vif, true))
			IWL_ERR(mvm, "Failed to update SF state\n");

	return ret;
}