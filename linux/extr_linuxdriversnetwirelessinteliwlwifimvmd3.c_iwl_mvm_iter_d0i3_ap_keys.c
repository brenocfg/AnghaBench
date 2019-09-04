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
struct iwl_mvm {size_t d0i3_ap_sta_id; int /*<<< orphan*/  hw; int /*<<< orphan*/ * fw_id_to_mac_id; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  ieee80211_iter_keys_rcu (int /*<<< orphan*/ ,struct ieee80211_vif*,void (*) (struct ieee80211_hw*,struct ieee80211_vif*,struct ieee80211_sta*,struct ieee80211_key_conf*,void*),void*) ; 
 struct ieee80211_sta* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static void
iwl_mvm_iter_d0i3_ap_keys(struct iwl_mvm *mvm,
			  struct ieee80211_vif *vif,
			  void (*iter)(struct ieee80211_hw *hw,
				       struct ieee80211_vif *vif,
				       struct ieee80211_sta *sta,
				       struct ieee80211_key_conf *key,
				       void *data),
			  void *data)
{
	struct ieee80211_sta *ap_sta;

	rcu_read_lock();

	ap_sta = rcu_dereference(mvm->fw_id_to_mac_id[mvm->d0i3_ap_sta_id]);
	if (IS_ERR_OR_NULL(ap_sta))
		goto out;

	ieee80211_iter_keys_rcu(mvm->hw, vif, iter, data);
out:
	rcu_read_unlock();
}