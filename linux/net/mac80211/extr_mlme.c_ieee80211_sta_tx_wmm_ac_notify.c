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
typedef  scalar_t__ u16 ;
struct ieee80211_if_managed {int /*<<< orphan*/  tx_tspec_wk; struct ieee80211_sta_tx_tspec* tx_tspec; } ;
struct TYPE_2__ {struct ieee80211_if_managed mgd; } ;
struct ieee80211_sub_if_data {TYPE_1__ u; } ;
struct ieee80211_sta_tx_tspec {scalar_t__ admitted_time; unsigned long time_slice_start; scalar_t__ consumed_tx_time; int downgraded; int /*<<< orphan*/  action; } ;
struct ieee80211_hdr {int dummy; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int /*<<< orphan*/  TX_TSPEC_ACTION_DOWNGRADE ; 
 int /*<<< orphan*/  TX_TSPEC_ACTION_STOP_DOWNGRADE ; 
 int ieee80211_ac_from_tid (scalar_t__) ; 
 scalar_t__ ieee80211_get_tid (struct ieee80211_hdr*) ; 
 unsigned long jiffies ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,scalar_t__) ; 

__attribute__((used)) static void ieee80211_sta_tx_wmm_ac_notify(struct ieee80211_sub_if_data *sdata,
					   struct ieee80211_hdr *hdr,
					   u16 tx_time)
{
	struct ieee80211_if_managed *ifmgd = &sdata->u.mgd;
	u16 tid = ieee80211_get_tid(hdr);
	int ac = ieee80211_ac_from_tid(tid);
	struct ieee80211_sta_tx_tspec *tx_tspec = &ifmgd->tx_tspec[ac];
	unsigned long now = jiffies;

	if (likely(!tx_tspec->admitted_time))
		return;

	if (time_after(now, tx_tspec->time_slice_start + HZ)) {
		tx_tspec->consumed_tx_time = 0;
		tx_tspec->time_slice_start = now;

		if (tx_tspec->downgraded) {
			tx_tspec->action = TX_TSPEC_ACTION_STOP_DOWNGRADE;
			schedule_delayed_work(&ifmgd->tx_tspec_wk, 0);
		}
	}

	if (tx_tspec->downgraded)
		return;

	tx_tspec->consumed_tx_time += tx_time;

	if (tx_tspec->consumed_tx_time >= tx_tspec->admitted_time) {
		tx_tspec->downgraded = true;
		tx_tspec->action = TX_TSPEC_ACTION_DOWNGRADE;
		schedule_delayed_work(&ifmgd->tx_tspec_wk, 0);
	}
}