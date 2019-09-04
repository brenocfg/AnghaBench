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
struct iwl_wowlan_status {int /*<<< orphan*/  num_of_gtk_rekeys; } ;
struct iwl_mvm_d3_gtk_iter_data {int find_phase; struct iwl_wowlan_status* status; struct iwl_mvm* mvm; } ;
struct iwl_mvm {int dummy; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_d3_update_keys ; 
 int /*<<< orphan*/  iwl_mvm_iter_d0i3_ap_keys (struct iwl_mvm*,struct ieee80211_vif*,int /*<<< orphan*/ ,struct iwl_mvm_d3_gtk_iter_data*) ; 

void iwl_mvm_d0i3_update_keys(struct iwl_mvm *mvm,
			      struct ieee80211_vif *vif,
			      struct iwl_wowlan_status *status)
{
	struct iwl_mvm_d3_gtk_iter_data gtkdata = {
		.mvm = mvm,
		.status = status,
	};

	/*
	 * rekey handling requires taking locks that can't be taken now.
	 * however, d0i3 doesn't offload rekey, so we're fine.
	 */
	if (WARN_ON_ONCE(status->num_of_gtk_rekeys))
		return;

	/* find last GTK that we used initially, if any */
	gtkdata.find_phase = true;
	iwl_mvm_iter_d0i3_ap_keys(mvm, vif, iwl_mvm_d3_update_keys, &gtkdata);

	gtkdata.find_phase = false;
	iwl_mvm_iter_d0i3_ap_keys(mvm, vif, iwl_mvm_d3_update_keys, &gtkdata);
}