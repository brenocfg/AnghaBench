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
struct tid_ampdu_tx {int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/  mtx; int /*<<< orphan*/  work; } ;
struct sta_info {TYPE_1__ ampdu_mlme; } ;
typedef  enum ieee80211_agg_stop_reason { ____Placeholder_ieee80211_agg_stop_reason } ieee80211_agg_stop_reason ;

/* Variables and functions */
 int AGG_STOP_DESTROY_STA ; 
 int AGG_STOP_PEER_REQUEST ; 
 int /*<<< orphan*/  HT_AGG_STATE_STOP_CB ; 
 int IEEE80211_NUM_TIDS ; 
 int /*<<< orphan*/  WLAN_BACK_RECIPIENT ; 
 int /*<<< orphan*/  WLAN_REASON_QSTA_LEAVE_QBSS ; 
 int /*<<< orphan*/  ___ieee80211_stop_rx_ba_session (struct sta_info*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ___ieee80211_stop_tx_ba_session (struct sta_info*,int,int) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_stop_tx_ba_cb (struct sta_info*,int,struct tid_ampdu_tx*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct tid_ampdu_tx* rcu_dereference_protected_tid_tx (struct sta_info*,int) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ieee80211_sta_tear_down_BA_sessions(struct sta_info *sta,
					 enum ieee80211_agg_stop_reason reason)
{
	int i;

	mutex_lock(&sta->ampdu_mlme.mtx);
	for (i = 0; i <  IEEE80211_NUM_TIDS; i++)
		___ieee80211_stop_rx_ba_session(sta, i, WLAN_BACK_RECIPIENT,
						WLAN_REASON_QSTA_LEAVE_QBSS,
						reason != AGG_STOP_DESTROY_STA &&
						reason != AGG_STOP_PEER_REQUEST);

	for (i = 0; i <  IEEE80211_NUM_TIDS; i++)
		___ieee80211_stop_tx_ba_session(sta, i, reason);
	mutex_unlock(&sta->ampdu_mlme.mtx);

	/*
	 * In case the tear down is part of a reconfigure due to HW restart
	 * request, it is possible that the low level driver requested to stop
	 * the BA session, so handle it to properly clean tid_tx data.
	 */
	if(reason == AGG_STOP_DESTROY_STA) {
		cancel_work_sync(&sta->ampdu_mlme.work);

		mutex_lock(&sta->ampdu_mlme.mtx);
		for (i = 0; i < IEEE80211_NUM_TIDS; i++) {
			struct tid_ampdu_tx *tid_tx =
				rcu_dereference_protected_tid_tx(sta, i);

			if (!tid_tx)
				continue;

			if (test_and_clear_bit(HT_AGG_STATE_STOP_CB, &tid_tx->state))
				ieee80211_stop_tx_ba_cb(sta, i, tid_tx);
		}
		mutex_unlock(&sta->ampdu_mlme.mtx);
	}
}