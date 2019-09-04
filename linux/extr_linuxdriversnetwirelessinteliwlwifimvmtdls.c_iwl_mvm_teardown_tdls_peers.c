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
struct iwl_mvm_sta {int /*<<< orphan*/  vif; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * fw_id_to_mac_id; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; int /*<<< orphan*/  tdls; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  NL80211_TDLS_TEARDOWN ; 
 int /*<<< orphan*/  WLAN_REASON_TDLS_TEARDOWN_UNSPECIFIED ; 
 int /*<<< orphan*/  ieee80211_tdls_oper_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct ieee80211_sta* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void iwl_mvm_teardown_tdls_peers(struct iwl_mvm *mvm)
{
	struct ieee80211_sta *sta;
	struct iwl_mvm_sta *mvmsta;
	int i;

	lockdep_assert_held(&mvm->mutex);

	for (i = 0; i < ARRAY_SIZE(mvm->fw_id_to_mac_id); i++) {
		sta = rcu_dereference_protected(mvm->fw_id_to_mac_id[i],
						lockdep_is_held(&mvm->mutex));
		if (!sta || IS_ERR(sta) || !sta->tdls)
			continue;

		mvmsta = iwl_mvm_sta_from_mac80211(sta);
		ieee80211_tdls_oper_request(mvmsta->vif, sta->addr,
				NL80211_TDLS_TEARDOWN,
				WLAN_REASON_TDLS_TEARDOWN_UNSPECIFIED,
				GFP_KERNEL);
	}
}