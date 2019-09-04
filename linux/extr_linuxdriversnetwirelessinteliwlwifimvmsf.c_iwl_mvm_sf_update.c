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
struct iwl_mvm_vif {int /*<<< orphan*/  ap_sta_id; } ;
struct iwl_mvm_active_iface_iterator_data {int sta_vif_state; int num_active_macs; int /*<<< orphan*/  sta_vif_ap_sta_id; struct ieee80211_vif* ignore_vif; } ;
struct iwl_mvm {int /*<<< orphan*/  hw; int /*<<< orphan*/  status; } ;
struct TYPE_2__ {int /*<<< orphan*/  dtim_period; int /*<<< orphan*/  assoc; } ;
struct ieee80211_vif {scalar_t__ type; TYPE_1__ bss_conf; } ;
typedef  enum iwl_sf_state { ____Placeholder_iwl_sf_state } iwl_sf_state ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_NORMAL ; 
 int /*<<< orphan*/  IWL_MVM_INVALID_STA ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_IN_HW_RESTART ; 
 scalar_t__ NL80211_IFTYPE_P2P_DEVICE ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int SF_FULL_ON ; 
 int SF_INIT_OFF ; 
 int SF_UNINIT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iwl_mvm_active_iface_iterator_data*) ; 
 int /*<<< orphan*/  iwl_mvm_bound_iface_iterator ; 
 int iwl_mvm_sf_config (struct iwl_mvm*,int /*<<< orphan*/ ,int) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int iwl_mvm_sf_update(struct iwl_mvm *mvm, struct ieee80211_vif *changed_vif,
		      bool remove_vif)
{
	enum iwl_sf_state new_state;
	u8 sta_id = IWL_MVM_INVALID_STA;
	struct iwl_mvm_vif *mvmvif = NULL;
	struct iwl_mvm_active_iface_iterator_data data = {
		.ignore_vif = changed_vif,
		.sta_vif_state = SF_UNINIT,
		.sta_vif_ap_sta_id = IWL_MVM_INVALID_STA,
	};

	/*
	 * Ignore the call if we are in HW Restart flow, or if the handled
	 * vif is a p2p device.
	 */
	if (test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status) ||
	    (changed_vif && changed_vif->type == NL80211_IFTYPE_P2P_DEVICE))
		return 0;

	ieee80211_iterate_active_interfaces_atomic(mvm->hw,
						   IEEE80211_IFACE_ITER_NORMAL,
						   iwl_mvm_bound_iface_iterator,
						   &data);

	/* If changed_vif exists and is not to be removed, add to the count */
	if (changed_vif && !remove_vif)
		data.num_active_macs++;

	switch (data.num_active_macs) {
	case 0:
		/* If there are no active macs - change state to SF_INIT_OFF */
		new_state = SF_INIT_OFF;
		break;
	case 1:
		if (remove_vif) {
			/* The one active mac left is of type station
			 * and we filled the relevant data during iteration
			 */
			new_state = data.sta_vif_state;
			sta_id = data.sta_vif_ap_sta_id;
		} else {
			if (WARN_ON(!changed_vif))
				return -EINVAL;
			if (changed_vif->type != NL80211_IFTYPE_STATION) {
				new_state = SF_UNINIT;
			} else if (changed_vif->bss_conf.assoc &&
				   changed_vif->bss_conf.dtim_period) {
				mvmvif = iwl_mvm_vif_from_mac80211(changed_vif);
				sta_id = mvmvif->ap_sta_id;
				new_state = SF_FULL_ON;
			} else {
				new_state = SF_INIT_OFF;
			}
		}
		break;
	default:
		/* If there are multiple active macs - change to SF_UNINIT */
		new_state = SF_UNINIT;
	}
	return iwl_mvm_sf_config(mvm, sta_id, new_state);
}