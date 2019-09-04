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
typedef  int u32 ;
struct iwl_mvm {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * fw_id_to_mac_id; int /*<<< orphan*/  trans; } ;
struct ieee80211_sta {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR_OR_NULL (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  iwl_mvm_flush_sta_tids (struct iwl_mvm*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_flush_tx_path (struct iwl_mvm*,int,int /*<<< orphan*/ ) ; 
 int iwl_mvm_flushable_queues (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_has_new_tx_api (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  iwl_mvm_wait_sta_queues_empty (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_trans_wait_tx_queues_empty (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ieee80211_sta* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_mvm_flush_no_vif(struct iwl_mvm *mvm, u32 queues, bool drop)
{
	int i;

	if (!iwl_mvm_has_new_tx_api(mvm)) {
		if (drop) {
			mutex_lock(&mvm->mutex);
			iwl_mvm_flush_tx_path(mvm,
				iwl_mvm_flushable_queues(mvm) & queues, 0);
			mutex_unlock(&mvm->mutex);
		} else {
			iwl_trans_wait_tx_queues_empty(mvm->trans, queues);
		}
		return;
	}

	mutex_lock(&mvm->mutex);
	for (i = 0; i < ARRAY_SIZE(mvm->fw_id_to_mac_id); i++) {
		struct ieee80211_sta *sta;

		sta = rcu_dereference_protected(mvm->fw_id_to_mac_id[i],
						lockdep_is_held(&mvm->mutex));
		if (IS_ERR_OR_NULL(sta))
			continue;

		if (drop)
			iwl_mvm_flush_sta_tids(mvm, i, 0xFF, 0);
		else
			iwl_mvm_wait_sta_queues_empty(mvm,
					iwl_mvm_sta_from_mac80211(sta));
	}
	mutex_unlock(&mvm->mutex);
}