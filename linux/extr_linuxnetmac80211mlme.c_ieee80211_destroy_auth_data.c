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
struct TYPE_8__ {struct ieee80211_mgd_auth_data* auth_data; scalar_t__ flags; int /*<<< orphan*/  bssid; int /*<<< orphan*/  timer; } ;
struct TYPE_9__ {TYPE_3__ mgd; } ;
struct ieee80211_sub_if_data {TYPE_4__ u; TYPE_2__* local; } ;
struct ieee80211_mgd_auth_data {TYPE_5__* bss; } ;
struct TYPE_10__ {int /*<<< orphan*/  bssid; } ;
struct TYPE_6__ {int /*<<< orphan*/  wiphy; } ;
struct TYPE_7__ {TYPE_1__ hw; int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSS_CHANGED_BSSID ; 
 int /*<<< orphan*/  cfg80211_put_bss (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_bss_info_change_notify (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_vif_release_channel (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  kfree (struct ieee80211_mgd_auth_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdata_assert_lock (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  sta_info_destroy_addr (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ieee80211_destroy_auth_data(struct ieee80211_sub_if_data *sdata,
					bool assoc)
{
	struct ieee80211_mgd_auth_data *auth_data = sdata->u.mgd.auth_data;

	sdata_assert_lock(sdata);

	if (!assoc) {
		/*
		 * we are not authenticated yet, the only timer that could be
		 * running is the timeout for the authentication response which
		 * which is not relevant anymore.
		 */
		del_timer_sync(&sdata->u.mgd.timer);
		sta_info_destroy_addr(sdata, auth_data->bss->bssid);

		eth_zero_addr(sdata->u.mgd.bssid);
		ieee80211_bss_info_change_notify(sdata, BSS_CHANGED_BSSID);
		sdata->u.mgd.flags = 0;
		mutex_lock(&sdata->local->mtx);
		ieee80211_vif_release_channel(sdata);
		mutex_unlock(&sdata->local->mtx);
	}

	cfg80211_put_bss(sdata->local->hw.wiphy, auth_data->bss);
	kfree(auth_data);
	sdata->u.mgd.auth_data = NULL;
}