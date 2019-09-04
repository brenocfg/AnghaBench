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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  work; int /*<<< orphan*/  tid_rx_timer_expired; } ;
struct sta_info {TYPE_1__ ampdu_mlme; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sub_if_data {struct ieee80211_local* local; } ;
struct ieee80211_local {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 struct sta_info* sta_info_get_bss (struct ieee80211_sub_if_data*,int /*<<< orphan*/  const*) ; 
 struct ieee80211_sub_if_data* vif_to_sdata (struct ieee80211_vif*) ; 

void ieee80211_rx_ba_timer_expired(struct ieee80211_vif *vif,
				   const u8 *addr, unsigned int tid)
{
	struct ieee80211_sub_if_data *sdata = vif_to_sdata(vif);
	struct ieee80211_local *local = sdata->local;
	struct sta_info *sta;

	rcu_read_lock();
	sta = sta_info_get_bss(sdata, addr);
	if (!sta)
		goto unlock;

	set_bit(tid, sta->ampdu_mlme.tid_rx_timer_expired);
	ieee80211_queue_work(&local->hw, &sta->ampdu_mlme.work);

 unlock:
	rcu_read_unlock();
}