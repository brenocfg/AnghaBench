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
struct TYPE_5__ {void* iftype; } ;
struct TYPE_4__ {void* type; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  work; int /*<<< orphan*/  skb_queue; int /*<<< orphan*/  encrypt_headroom; TYPE_2__ wdev; int /*<<< orphan*/  name; TYPE_1__ vif; struct ieee80211_local* local; } ;
struct TYPE_6__ {int /*<<< orphan*/  wiphy; scalar_t__ vif_data_size; } ;
struct ieee80211_local {int /*<<< orphan*/  iflist_mtx; scalar_t__ monitor_sdata; int /*<<< orphan*/  mtx; int /*<<< orphan*/  monitor_chandef; TYPE_3__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IEEE80211_CHANCTX_EXCLUSIVE ; 
 int /*<<< orphan*/  IEEE80211_ENCRYPT_HEADROOM ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* NL80211_IFTYPE_MONITOR ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WANT_MONITOR_VIF ; 
 scalar_t__ WARN_ON (int) ; 
 int drv_add_interface (struct ieee80211_local*,struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  drv_remove_interface (struct ieee80211_local*,struct ieee80211_sub_if_data*) ; 
 int ieee80211_check_queues (struct ieee80211_sub_if_data*,void*) ; 
 int /*<<< orphan*/  ieee80211_hw_check (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_iface_work ; 
 int /*<<< orphan*/  ieee80211_set_default_queues (struct ieee80211_sub_if_data*) ; 
 int ieee80211_vif_use_channel (struct ieee80211_sub_if_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ieee80211_sub_if_data*) ; 
 struct ieee80211_sub_if_data* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (scalar_t__,struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  synchronize_net () ; 
 char* wiphy_name (int /*<<< orphan*/ ) ; 

int ieee80211_add_virtual_monitor(struct ieee80211_local *local)
{
	struct ieee80211_sub_if_data *sdata;
	int ret;

	if (!ieee80211_hw_check(&local->hw, WANT_MONITOR_VIF))
		return 0;

	ASSERT_RTNL();

	if (local->monitor_sdata)
		return 0;

	sdata = kzalloc(sizeof(*sdata) + local->hw.vif_data_size, GFP_KERNEL);
	if (!sdata)
		return -ENOMEM;

	/* set up data */
	sdata->local = local;
	sdata->vif.type = NL80211_IFTYPE_MONITOR;
	snprintf(sdata->name, IFNAMSIZ, "%s-monitor",
		 wiphy_name(local->hw.wiphy));
	sdata->wdev.iftype = NL80211_IFTYPE_MONITOR;

	sdata->encrypt_headroom = IEEE80211_ENCRYPT_HEADROOM;

	ieee80211_set_default_queues(sdata);

	ret = drv_add_interface(local, sdata);
	if (WARN_ON(ret)) {
		/* ok .. stupid driver, it asked for this! */
		kfree(sdata);
		return ret;
	}

	ret = ieee80211_check_queues(sdata, NL80211_IFTYPE_MONITOR);
	if (ret) {
		kfree(sdata);
		return ret;
	}

	mutex_lock(&local->iflist_mtx);
	rcu_assign_pointer(local->monitor_sdata, sdata);
	mutex_unlock(&local->iflist_mtx);

	mutex_lock(&local->mtx);
	ret = ieee80211_vif_use_channel(sdata, &local->monitor_chandef,
					IEEE80211_CHANCTX_EXCLUSIVE);
	mutex_unlock(&local->mtx);
	if (ret) {
		mutex_lock(&local->iflist_mtx);
		RCU_INIT_POINTER(local->monitor_sdata, NULL);
		mutex_unlock(&local->iflist_mtx);
		synchronize_net();
		drv_remove_interface(local, sdata);
		kfree(sdata);
		return ret;
	}

	skb_queue_head_init(&sdata->skb_queue);
	INIT_WORK(&sdata->work, ieee80211_iface_work);

	return 0;
}