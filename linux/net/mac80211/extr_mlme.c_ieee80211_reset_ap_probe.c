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
struct ieee80211_if_managed {int flags; int /*<<< orphan*/  conn_mon_timer; } ;
struct TYPE_2__ {struct ieee80211_if_managed mgd; } ;
struct ieee80211_sub_if_data {struct ieee80211_local* local; TYPE_1__ u; } ;
struct ieee80211_local {int /*<<< orphan*/  mtx; int /*<<< orphan*/  hw; int /*<<< orphan*/  iflist_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONNECTION_MONITOR ; 
 scalar_t__ IEEE80211_CONNECTION_IDLE_TIME ; 
 int IEEE80211_STA_CONNECTION_POLL ; 
 int /*<<< orphan*/  __ieee80211_stop_poll (struct ieee80211_sub_if_data*) ; 
 scalar_t__ ieee80211_hw_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_recalc_ps (struct ieee80211_local*) ; 
 int /*<<< orphan*/  ieee80211_sta_reset_beacon_monitor (struct ieee80211_sub_if_data*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  round_jiffies_up (scalar_t__) ; 

__attribute__((used)) static void ieee80211_reset_ap_probe(struct ieee80211_sub_if_data *sdata)
{
	struct ieee80211_if_managed *ifmgd = &sdata->u.mgd;
	struct ieee80211_local *local = sdata->local;

	mutex_lock(&local->mtx);
	if (!(ifmgd->flags & IEEE80211_STA_CONNECTION_POLL))
		goto out;

	__ieee80211_stop_poll(sdata);

	mutex_lock(&local->iflist_mtx);
	ieee80211_recalc_ps(local);
	mutex_unlock(&local->iflist_mtx);

	if (ieee80211_hw_check(&sdata->local->hw, CONNECTION_MONITOR))
		goto out;

	/*
	 * We've received a probe response, but are not sure whether
	 * we have or will be receiving any beacons or data, so let's
	 * schedule the timers again, just in case.
	 */
	ieee80211_sta_reset_beacon_monitor(sdata);

	mod_timer(&ifmgd->conn_mon_timer,
		  round_jiffies_up(jiffies +
				   IEEE80211_CONNECTION_IDLE_TIME));
out:
	mutex_unlock(&local->mtx);
}