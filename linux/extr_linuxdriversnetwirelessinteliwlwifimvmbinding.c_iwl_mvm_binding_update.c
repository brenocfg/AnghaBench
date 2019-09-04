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
typedef  int /*<<< orphan*/  u32 ;
struct iwl_mvm_vif {int /*<<< orphan*/  color; int /*<<< orphan*/  id; } ;
struct iwl_mvm_phy_ctxt {int dummy; } ;
struct iwl_mvm_iface_iterator_data {size_t idx; int /*<<< orphan*/ * colors; int /*<<< orphan*/ * ids; struct iwl_mvm_phy_ctxt* phyctxt; struct ieee80211_vif* ignore_vif; } ;
struct iwl_mvm {int /*<<< orphan*/  hw; int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FW_CTXT_ACTION_ADD ; 
 int /*<<< orphan*/  FW_CTXT_ACTION_MODIFY ; 
 int /*<<< orphan*/  FW_CTXT_ACTION_REMOVE ; 
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_NORMAL ; 
 size_t MAX_MACS_IN_BINDING ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iwl_mvm_iface_iterator_data*) ; 
 int iwl_mvm_binding_cmd (struct iwl_mvm*,int /*<<< orphan*/ ,struct iwl_mvm_iface_iterator_data*) ; 
 int /*<<< orphan*/  iwl_mvm_iface_iterator ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_mvm_binding_update(struct iwl_mvm *mvm,
				  struct ieee80211_vif *vif,
				  struct iwl_mvm_phy_ctxt *phyctxt,
				  bool add)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_mvm_iface_iterator_data data = {
		.ignore_vif = vif,
		.phyctxt = phyctxt,
	};
	u32 action = FW_CTXT_ACTION_MODIFY;

	lockdep_assert_held(&mvm->mutex);

	ieee80211_iterate_active_interfaces_atomic(mvm->hw,
						   IEEE80211_IFACE_ITER_NORMAL,
						   iwl_mvm_iface_iterator,
						   &data);

	/*
	 * If there are no other interfaces yet we
	 * need to create a new binding.
	 */
	if (data.idx == 0) {
		if (add)
			action = FW_CTXT_ACTION_ADD;
		else
			action = FW_CTXT_ACTION_REMOVE;
	}

	if (add) {
		if (WARN_ON_ONCE(data.idx >= MAX_MACS_IN_BINDING))
			return -EINVAL;

		data.ids[data.idx] = mvmvif->id;
		data.colors[data.idx] = mvmvif->color;
		data.idx++;
	}

	return iwl_mvm_binding_cmd(mvm, action, &data);
}