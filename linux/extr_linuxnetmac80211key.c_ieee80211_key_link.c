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
struct sta_info {int /*<<< orphan*/ * gtk; int /*<<< orphan*/ * ptk; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct ieee80211_sub_if_data {struct ieee80211_local* local; int /*<<< orphan*/ * keys; TYPE_2__ vif; } ;
struct ieee80211_local {int /*<<< orphan*/  key_mtx; int /*<<< orphan*/  wowlan; } ;
struct TYPE_3__ {int keyidx; int flags; } ;
struct ieee80211_key {struct sta_info* sta; struct ieee80211_sub_if_data* sdata; struct ieee80211_local* local; TYPE_1__ conf; } ;

/* Variables and functions */
 int IEEE80211_KEY_FLAG_PAIRWISE ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  ieee80211_debugfs_key_add (struct ieee80211_key*) ; 
 int /*<<< orphan*/  ieee80211_key_destroy (struct ieee80211_key*,int) ; 
 int ieee80211_key_enable_hw_accel (struct ieee80211_key*) ; 
 int /*<<< orphan*/  ieee80211_key_free (struct ieee80211_key*,int) ; 
 int /*<<< orphan*/  ieee80211_key_free_unused (struct ieee80211_key*) ; 
 scalar_t__ ieee80211_key_identical (struct ieee80211_sub_if_data*,struct ieee80211_key*,struct ieee80211_key*) ; 
 int /*<<< orphan*/  ieee80211_key_replace (struct ieee80211_sub_if_data*,struct sta_info*,int,struct ieee80211_key*,struct ieee80211_key*) ; 
 int /*<<< orphan*/  increment_tailroom_need_count (struct ieee80211_sub_if_data*) ; 
 struct ieee80211_key* key_mtx_dereference (struct ieee80211_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int ieee80211_key_link(struct ieee80211_key *key,
		       struct ieee80211_sub_if_data *sdata,
		       struct sta_info *sta)
{
	struct ieee80211_local *local = sdata->local;
	struct ieee80211_key *old_key;
	int idx = key->conf.keyidx;
	bool pairwise = key->conf.flags & IEEE80211_KEY_FLAG_PAIRWISE;
	/*
	 * We want to delay tailroom updates only for station - in that
	 * case it helps roaming speed, but in other cases it hurts and
	 * can cause warnings to appear.
	 */
	bool delay_tailroom = sdata->vif.type == NL80211_IFTYPE_STATION;
	int ret;

	mutex_lock(&sdata->local->key_mtx);

	if (sta && pairwise)
		old_key = key_mtx_dereference(sdata->local, sta->ptk[idx]);
	else if (sta)
		old_key = key_mtx_dereference(sdata->local, sta->gtk[idx]);
	else
		old_key = key_mtx_dereference(sdata->local, sdata->keys[idx]);

	/*
	 * Silently accept key re-installation without really installing the
	 * new version of the key to avoid nonce reuse or replay issues.
	 */
	if (ieee80211_key_identical(sdata, old_key, key)) {
		ieee80211_key_free_unused(key);
		ret = 0;
		goto out;
	}

	key->local = sdata->local;
	key->sdata = sdata;
	key->sta = sta;

	increment_tailroom_need_count(sdata);

	ieee80211_key_replace(sdata, sta, pairwise, old_key, key);
	ieee80211_key_destroy(old_key, delay_tailroom);

	ieee80211_debugfs_key_add(key);

	if (!local->wowlan) {
		ret = ieee80211_key_enable_hw_accel(key);
		if (ret)
			ieee80211_key_free(key, delay_tailroom);
	} else {
		ret = 0;
	}

 out:
	mutex_unlock(&sdata->local->key_mtx);

	return ret;
}