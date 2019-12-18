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
struct ieee80211_sub_if_data {int dummy; } ;
struct ieee80211_local {int /*<<< orphan*/  mtx; int /*<<< orphan*/  iflist_mtx; int /*<<< orphan*/  monitor_sdata; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WANT_MONITOR_VIF ; 
 int /*<<< orphan*/  drv_remove_interface (struct ieee80211_local*,struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_hw_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_vif_release_channel (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  kfree (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ieee80211_sub_if_data* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_net () ; 

void ieee80211_del_virtual_monitor(struct ieee80211_local *local)
{
	struct ieee80211_sub_if_data *sdata;

	if (!ieee80211_hw_check(&local->hw, WANT_MONITOR_VIF))
		return;

	ASSERT_RTNL();

	mutex_lock(&local->iflist_mtx);

	sdata = rcu_dereference_protected(local->monitor_sdata,
					  lockdep_is_held(&local->iflist_mtx));
	if (!sdata) {
		mutex_unlock(&local->iflist_mtx);
		return;
	}

	RCU_INIT_POINTER(local->monitor_sdata, NULL);
	mutex_unlock(&local->iflist_mtx);

	synchronize_net();

	mutex_lock(&local->mtx);
	ieee80211_vif_release_channel(sdata);
	mutex_unlock(&local->mtx);

	drv_remove_interface(local, sdata);

	kfree(sdata);
}