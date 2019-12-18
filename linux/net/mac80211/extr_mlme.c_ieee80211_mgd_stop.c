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
struct ieee80211_if_managed {int /*<<< orphan*/  timer; int /*<<< orphan*/  teardown_lock; scalar_t__ assoc_req_ies_len; int /*<<< orphan*/ * assoc_req_ies; int /*<<< orphan*/ * orig_teardown_skb; int /*<<< orphan*/ * teardown_skb; scalar_t__ auth_data; TYPE_2__* assoc_data; int /*<<< orphan*/  tdls_peer_del_work; int /*<<< orphan*/  chswitch_work; int /*<<< orphan*/  csa_connection_drop_work; int /*<<< orphan*/  request_smps_work; int /*<<< orphan*/  beacon_connection_loss_work; int /*<<< orphan*/  monitor_work; } ;
struct TYPE_3__ {struct ieee80211_if_managed mgd; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  dev; TYPE_1__ u; } ;
struct cfg80211_bss {int dummy; } ;
struct TYPE_4__ {struct cfg80211_bss* bss; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfg80211_assoc_timeout (int /*<<< orphan*/ ,struct cfg80211_bss*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_destroy_assoc_data (struct ieee80211_sub_if_data*,int,int) ; 
 int /*<<< orphan*/  ieee80211_destroy_auth_data (struct ieee80211_sub_if_data*,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdata_lock (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  sdata_unlock (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void ieee80211_mgd_stop(struct ieee80211_sub_if_data *sdata)
{
	struct ieee80211_if_managed *ifmgd = &sdata->u.mgd;

	/*
	 * Make sure some work items will not run after this,
	 * they will not do anything but might not have been
	 * cancelled when disconnecting.
	 */
	cancel_work_sync(&ifmgd->monitor_work);
	cancel_work_sync(&ifmgd->beacon_connection_loss_work);
	cancel_work_sync(&ifmgd->request_smps_work);
	cancel_work_sync(&ifmgd->csa_connection_drop_work);
	cancel_work_sync(&ifmgd->chswitch_work);
	cancel_delayed_work_sync(&ifmgd->tdls_peer_del_work);

	sdata_lock(sdata);
	if (ifmgd->assoc_data) {
		struct cfg80211_bss *bss = ifmgd->assoc_data->bss;
		ieee80211_destroy_assoc_data(sdata, false, false);
		cfg80211_assoc_timeout(sdata->dev, bss);
	}
	if (ifmgd->auth_data)
		ieee80211_destroy_auth_data(sdata, false);
	spin_lock_bh(&ifmgd->teardown_lock);
	if (ifmgd->teardown_skb) {
		kfree_skb(ifmgd->teardown_skb);
		ifmgd->teardown_skb = NULL;
		ifmgd->orig_teardown_skb = NULL;
	}
	kfree(ifmgd->assoc_req_ies);
	ifmgd->assoc_req_ies = NULL;
	ifmgd->assoc_req_ies_len = 0;
	spin_unlock_bh(&ifmgd->teardown_lock);
	del_timer_sync(&ifmgd->timer);
	sdata_unlock(sdata);
}