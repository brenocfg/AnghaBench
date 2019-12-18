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
struct TYPE_3__ {scalar_t__ txq; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  wdev; scalar_t__ dev; TYPE_1__ vif; TYPE_2__* local; int /*<<< orphan*/  list; } ;
struct TYPE_4__ {int /*<<< orphan*/  iflist_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  cfg80211_unregister_wdev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_teardown_sdata (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_txq_purge (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  to_txq_info (scalar_t__) ; 
 int /*<<< orphan*/  unregister_netdevice (scalar_t__) ; 

void ieee80211_if_remove(struct ieee80211_sub_if_data *sdata)
{
	ASSERT_RTNL();

	mutex_lock(&sdata->local->iflist_mtx);
	list_del_rcu(&sdata->list);
	mutex_unlock(&sdata->local->iflist_mtx);

	if (sdata->vif.txq)
		ieee80211_txq_purge(sdata->local, to_txq_info(sdata->vif.txq));

	synchronize_rcu();

	if (sdata->dev) {
		unregister_netdevice(sdata->dev);
	} else {
		cfg80211_unregister_wdev(&sdata->wdev);
		ieee80211_teardown_sdata(sdata);
		kfree(sdata);
	}
}