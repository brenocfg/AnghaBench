#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct ieee80211_mgd_assoc_data* assoc_data; scalar_t__ flags; int /*<<< orphan*/  bssid; int /*<<< orphan*/  timer; } ;
struct TYPE_9__ {TYPE_3__ mgd; } ;
struct TYPE_6__ {int mu_mimo_owner; } ;
struct ieee80211_sub_if_data {TYPE_4__ u; int /*<<< orphan*/  dev; TYPE_2__* local; TYPE_1__ vif; } ;
struct ieee80211_mgd_assoc_data {TYPE_5__* bss; } ;
struct TYPE_10__ {int /*<<< orphan*/  bssid; } ;
struct TYPE_7__ {int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSS_CHANGED_BSSID ; 
 int /*<<< orphan*/  cfg80211_abandon_assoc (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_bss_info_change_notify (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_vif_release_channel (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  kfree (struct ieee80211_mgd_assoc_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdata_assert_lock (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  sta_info_destroy_addr (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ieee80211_destroy_assoc_data(struct ieee80211_sub_if_data *sdata,
					 bool assoc, bool abandon)
{
	struct ieee80211_mgd_assoc_data *assoc_data = sdata->u.mgd.assoc_data;

	sdata_assert_lock(sdata);

	if (!assoc) {
		/*
		 * we are not associated yet, the only timer that could be
		 * running is the timeout for the association response which
		 * which is not relevant anymore.
		 */
		del_timer_sync(&sdata->u.mgd.timer);
		sta_info_destroy_addr(sdata, assoc_data->bss->bssid);

		eth_zero_addr(sdata->u.mgd.bssid);
		ieee80211_bss_info_change_notify(sdata, BSS_CHANGED_BSSID);
		sdata->u.mgd.flags = 0;
		sdata->vif.mu_mimo_owner = false;

		mutex_lock(&sdata->local->mtx);
		ieee80211_vif_release_channel(sdata);
		mutex_unlock(&sdata->local->mtx);

		if (abandon)
			cfg80211_abandon_assoc(sdata->dev, assoc_data->bss);
	}

	kfree(assoc_data);
	sdata->u.mgd.assoc_data = NULL;
}