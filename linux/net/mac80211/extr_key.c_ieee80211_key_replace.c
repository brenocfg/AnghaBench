#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sta_info {int ptk_idx; int /*<<< orphan*/ * gtk; int /*<<< orphan*/ * ptk; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/ * keys; int /*<<< orphan*/  default_mgmt_key; int /*<<< orphan*/  local; int /*<<< orphan*/  default_multicast_key; int /*<<< orphan*/  default_unicast_key; int /*<<< orphan*/  key_list; } ;
struct TYPE_4__ {int keyidx; int flags; } ;
struct ieee80211_key {int flags; int /*<<< orphan*/  list; TYPE_2__ conf; TYPE_1__* local; } ;
struct TYPE_3__ {int /*<<< orphan*/  wowlan; } ;

/* Variables and functions */
 int IEEE80211_KEY_FLAG_NO_AUTO_TX ; 
 int KEY_FLAG_UPLOADED_TO_HARDWARE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WLAN_STA_BLOCK_BA ; 
 int /*<<< orphan*/  __ieee80211_set_default_key (struct ieee80211_sub_if_data*,int,int,int) ; 
 int /*<<< orphan*/  __ieee80211_set_default_mgmt_key (struct ieee80211_sub_if_data*,int) ; 
 int /*<<< orphan*/  clear_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_check_fast_rx (struct sta_info*) ; 
 int /*<<< orphan*/  ieee80211_check_fast_xmit (struct sta_info*) ; 
 int /*<<< orphan*/  ieee80211_key_disable_hw_accel (struct ieee80211_key*) ; 
 int ieee80211_key_enable_hw_accel (struct ieee80211_key*) ; 
 int /*<<< orphan*/  ieee80211_pairwise_rekey (struct ieee80211_key*,struct ieee80211_key*) ; 
 struct ieee80211_key* key_mtx_dereference (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct ieee80211_key*) ; 

__attribute__((used)) static int ieee80211_key_replace(struct ieee80211_sub_if_data *sdata,
				  struct sta_info *sta,
				  bool pairwise,
				  struct ieee80211_key *old,
				  struct ieee80211_key *new)
{
	int idx;
	int ret = 0;
	bool defunikey, defmultikey, defmgmtkey;

	/* caller must provide at least one old/new */
	if (WARN_ON(!new && !old))
		return 0;

	if (new)
		list_add_tail_rcu(&new->list, &sdata->key_list);

	WARN_ON(new && old && new->conf.keyidx != old->conf.keyidx);

	if (new && sta && pairwise) {
		/* Unicast rekey needs special handling. With Extended Key ID
		 * old is still NULL for the first rekey.
		 */
		ieee80211_pairwise_rekey(old, new);
	}

	if (old) {
		idx = old->conf.keyidx;

		if (old->flags & KEY_FLAG_UPLOADED_TO_HARDWARE) {
			ieee80211_key_disable_hw_accel(old);

			if (new)
				ret = ieee80211_key_enable_hw_accel(new);
		}
	} else {
		/* new must be provided in case old is not */
		idx = new->conf.keyidx;
		if (!new->local->wowlan)
			ret = ieee80211_key_enable_hw_accel(new);
	}

	if (ret)
		return ret;

	if (sta) {
		if (pairwise) {
			rcu_assign_pointer(sta->ptk[idx], new);
			if (new &&
			    !(new->conf.flags & IEEE80211_KEY_FLAG_NO_AUTO_TX)) {
				sta->ptk_idx = idx;
				clear_sta_flag(sta, WLAN_STA_BLOCK_BA);
				ieee80211_check_fast_xmit(sta);
			}
		} else {
			rcu_assign_pointer(sta->gtk[idx], new);
		}
		/* Only needed for transition from no key -> key.
		 * Still triggers unnecessary when using Extended Key ID
		 * and installing the second key ID the first time.
		 */
		if (new && !old)
			ieee80211_check_fast_rx(sta);
	} else {
		defunikey = old &&
			old == key_mtx_dereference(sdata->local,
						sdata->default_unicast_key);
		defmultikey = old &&
			old == key_mtx_dereference(sdata->local,
						sdata->default_multicast_key);
		defmgmtkey = old &&
			old == key_mtx_dereference(sdata->local,
						sdata->default_mgmt_key);

		if (defunikey && !new)
			__ieee80211_set_default_key(sdata, -1, true, false);
		if (defmultikey && !new)
			__ieee80211_set_default_key(sdata, -1, false, true);
		if (defmgmtkey && !new)
			__ieee80211_set_default_mgmt_key(sdata, -1);

		rcu_assign_pointer(sdata->keys[idx], new);
		if (defunikey && new)
			__ieee80211_set_default_key(sdata, new->conf.keyidx,
						    true, false);
		if (defmultikey && new)
			__ieee80211_set_default_key(sdata, new->conf.keyidx,
						    false, true);
		if (defmgmtkey && new)
			__ieee80211_set_default_mgmt_key(sdata,
							 new->conf.keyidx);
	}

	if (old)
		list_del_rcu(&old->list);

	return 0;
}