#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sta_info {int /*<<< orphan*/ * ptk; int /*<<< orphan*/ * gtk; } ;
struct ieee80211_local {int /*<<< orphan*/  key_mtx; } ;
struct TYPE_4__ {int flags; } ;
struct ieee80211_key {TYPE_3__* sdata; TYPE_1__ conf; int /*<<< orphan*/  sta; } ;
struct TYPE_5__ {scalar_t__ type; } ;
struct TYPE_6__ {TYPE_2__ vif; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int IEEE80211_KEY_FLAG_PAIRWISE ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int NUM_DEFAULT_KEYS ; 
 int /*<<< orphan*/  __ieee80211_key_destroy (struct ieee80211_key*,int) ; 
 int /*<<< orphan*/  ieee80211_key_replace (TYPE_3__*,int /*<<< orphan*/ ,int,struct ieee80211_key*,int /*<<< orphan*/ *) ; 
 struct ieee80211_key* key_mtx_dereference (struct ieee80211_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void ieee80211_free_sta_keys(struct ieee80211_local *local,
			     struct sta_info *sta)
{
	struct ieee80211_key *key;
	int i;

	mutex_lock(&local->key_mtx);
	for (i = 0; i < ARRAY_SIZE(sta->gtk); i++) {
		key = key_mtx_dereference(local, sta->gtk[i]);
		if (!key)
			continue;
		ieee80211_key_replace(key->sdata, key->sta,
				key->conf.flags & IEEE80211_KEY_FLAG_PAIRWISE,
				key, NULL);
		__ieee80211_key_destroy(key, key->sdata->vif.type ==
					NL80211_IFTYPE_STATION);
	}

	for (i = 0; i < NUM_DEFAULT_KEYS; i++) {
		key = key_mtx_dereference(local, sta->ptk[i]);
		if (!key)
			continue;
		ieee80211_key_replace(key->sdata, key->sta,
				key->conf.flags & IEEE80211_KEY_FLAG_PAIRWISE,
				key, NULL);
		__ieee80211_key_destroy(key, key->sdata->vif.type ==
					NL80211_IFTYPE_STATION);
	}

	mutex_unlock(&local->key_mtx);
}