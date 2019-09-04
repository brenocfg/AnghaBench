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
struct ieee80211_sub_if_data {int /*<<< orphan*/  default_mgmt_key; int /*<<< orphan*/ * keys; int /*<<< orphan*/  local; } ;
struct ieee80211_key {int dummy; } ;

/* Variables and functions */
 int NUM_DEFAULT_KEYS ; 
 int NUM_DEFAULT_MGMT_KEYS ; 
 int /*<<< orphan*/  assert_key_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_debugfs_key_update_default (struct ieee80211_sub_if_data*) ; 
 struct ieee80211_key* key_mtx_dereference (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct ieee80211_key*) ; 

__attribute__((used)) static void
__ieee80211_set_default_mgmt_key(struct ieee80211_sub_if_data *sdata, int idx)
{
	struct ieee80211_key *key = NULL;

	assert_key_lock(sdata->local);

	if (idx >= NUM_DEFAULT_KEYS &&
	    idx < NUM_DEFAULT_KEYS + NUM_DEFAULT_MGMT_KEYS)
		key = key_mtx_dereference(sdata->local, sdata->keys[idx]);

	rcu_assign_pointer(sdata->default_mgmt_key, key);

	ieee80211_debugfs_key_update_default(sdata);
}