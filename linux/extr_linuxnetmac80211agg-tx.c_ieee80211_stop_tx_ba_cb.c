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
struct tid_ampdu_tx {scalar_t__ stop_initiator; scalar_t__ tx_stop; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct sta_info {TYPE_1__ sta; int /*<<< orphan*/  lock; struct ieee80211_sub_if_data* sdata; } ;
struct ieee80211_sub_if_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HT_AGG_STATE_STOPPING ; 
 scalar_t__ WLAN_BACK_INITIATOR ; 
 int /*<<< orphan*/  WLAN_REASON_QSTA_NOT_USE ; 
 int /*<<< orphan*/  ht_dbg (struct ieee80211_sub_if_data*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ieee80211_remove_tid_tx (struct sta_info*,int) ; 
 int /*<<< orphan*/  ieee80211_send_delba (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ieee80211_stop_tx_ba_cb(struct sta_info *sta, int tid,
			     struct tid_ampdu_tx *tid_tx)
{
	struct ieee80211_sub_if_data *sdata = sta->sdata;
	bool send_delba = false;

	ht_dbg(sdata, "Stopping Tx BA session for %pM tid %d\n",
	       sta->sta.addr, tid);

	spin_lock_bh(&sta->lock);

	if (!test_bit(HT_AGG_STATE_STOPPING, &tid_tx->state)) {
		ht_dbg(sdata,
		       "unexpected callback to A-MPDU stop for %pM tid %d\n",
		       sta->sta.addr, tid);
		goto unlock_sta;
	}

	if (tid_tx->stop_initiator == WLAN_BACK_INITIATOR && tid_tx->tx_stop)
		send_delba = true;

	ieee80211_remove_tid_tx(sta, tid);

 unlock_sta:
	spin_unlock_bh(&sta->lock);

	if (send_delba)
		ieee80211_send_delba(sdata, sta->sta.addr, tid,
			WLAN_BACK_INITIATOR, WLAN_REASON_QSTA_NOT_USE);
}