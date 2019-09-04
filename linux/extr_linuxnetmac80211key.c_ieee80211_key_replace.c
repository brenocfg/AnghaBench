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
struct sta_info {int ptk_idx; int /*<<< orphan*/ * gtk; int /*<<< orphan*/ * ptk; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/ * keys; int /*<<< orphan*/  default_mgmt_key; int /*<<< orphan*/  local; int /*<<< orphan*/  default_multicast_key; int /*<<< orphan*/  default_unicast_key; int /*<<< orphan*/  key_list; } ;
struct TYPE_2__ {int keyidx; } ;
struct ieee80211_key {int /*<<< orphan*/  list; TYPE_1__ conf; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __ieee80211_set_default_key (struct ieee80211_sub_if_data*,int,int,int) ; 
 int /*<<< orphan*/  __ieee80211_set_default_mgmt_key (struct ieee80211_sub_if_data*,int) ; 
 int /*<<< orphan*/  ieee80211_check_fast_rx (struct sta_info*) ; 
 int /*<<< orphan*/  ieee80211_check_fast_xmit (struct sta_info*) ; 
 struct ieee80211_key* key_mtx_dereference (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct ieee80211_key*) ; 

__attribute__((used)) static void ieee80211_key_replace(struct ieee80211_sub_if_data *sdata,
				  struct sta_info *sta,
				  bool pairwise,
				  struct ieee80211_key *old,
				  struct ieee80211_key *new)
{
	int idx;
	bool defunikey, defmultikey, defmgmtkey;

	/* caller must provide at least one old/new */
	if (WARN_ON(!new && !old))
		return;

	if (new)
		list_add_tail_rcu(&new->list, &sdata->key_list);

	WARN_ON(new && old && new->conf.keyidx != old->conf.keyidx);

	if (old)
		idx = old->conf.keyidx;
	else
		idx = new->conf.keyidx;

	if (sta) {
		if (pairwise) {
			rcu_assign_pointer(sta->ptk[idx], new);
			sta->ptk_idx = idx;
			ieee80211_check_fast_xmit(sta);
		} else {
			rcu_assign_pointer(sta->gtk[idx], new);
		}
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
}