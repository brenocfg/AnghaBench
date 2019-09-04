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
struct iwl_mvm_hw_queues_iface_iterator_data {int used_hw_queues; struct ieee80211_vif* exclude_vif; } ;
struct iwl_mvm {int /*<<< orphan*/  hw; int /*<<< orphan*/  mutex; int /*<<< orphan*/  aux_queue; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_RESUME_ALL ; 
 int /*<<< orphan*/  IWL_MVM_DQA_GCAST_QUEUE ; 
 int /*<<< orphan*/  IWL_MVM_OFFCHANNEL_QUEUE ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iwl_mvm_hw_queues_iface_iterator_data*) ; 
 int /*<<< orphan*/  iwl_mvm_iface_hw_queues_iter ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

unsigned long iwl_mvm_get_used_hw_queues(struct iwl_mvm *mvm,
					 struct ieee80211_vif *exclude_vif)
{
	struct iwl_mvm_hw_queues_iface_iterator_data data = {
		.exclude_vif = exclude_vif,
		.used_hw_queues =
			BIT(IWL_MVM_OFFCHANNEL_QUEUE) |
			BIT(mvm->aux_queue) |
			BIT(IWL_MVM_DQA_GCAST_QUEUE),
	};

	lockdep_assert_held(&mvm->mutex);

	/* mark all VIF used hw queues */
	ieee80211_iterate_active_interfaces_atomic(
		mvm->hw, IEEE80211_IFACE_ITER_RESUME_ALL,
		iwl_mvm_iface_hw_queues_iter, &data);

	return data.used_hw_queues;
}