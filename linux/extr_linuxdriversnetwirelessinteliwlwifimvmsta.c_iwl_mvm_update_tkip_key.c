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
typedef  int /*<<< orphan*/  u16 ;
struct iwl_mvm_sta {int /*<<< orphan*/  sta_id; } ;
struct iwl_mvm {int dummy; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int mfp; } ;
struct ieee80211_key_conf {int flags; int /*<<< orphan*/  hw_key_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ASYNC ; 
 int IEEE80211_KEY_FLAG_PAIRWISE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 struct iwl_mvm_sta* iwl_mvm_get_key_sta (struct iwl_mvm*,struct ieee80211_vif*,struct ieee80211_sta*) ; 
 int /*<<< orphan*/  iwl_mvm_send_sta_key (struct iwl_mvm*,int /*<<< orphan*/ ,struct ieee80211_key_conf*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

void iwl_mvm_update_tkip_key(struct iwl_mvm *mvm,
			     struct ieee80211_vif *vif,
			     struct ieee80211_key_conf *keyconf,
			     struct ieee80211_sta *sta, u32 iv32,
			     u16 *phase1key)
{
	struct iwl_mvm_sta *mvm_sta;
	bool mcast = !(keyconf->flags & IEEE80211_KEY_FLAG_PAIRWISE);
	bool mfp = sta ? sta->mfp : false;

	rcu_read_lock();

	mvm_sta = iwl_mvm_get_key_sta(mvm, vif, sta);
	if (WARN_ON_ONCE(!mvm_sta))
		goto unlock;
	iwl_mvm_send_sta_key(mvm, mvm_sta->sta_id, keyconf, mcast,
			     iv32, phase1key, CMD_ASYNC, keyconf->hw_key_idx,
			     mfp);

 unlock:
	rcu_read_unlock();
}