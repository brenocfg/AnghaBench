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
typedef  size_t u16 ;
struct tid_ampdu_rx {int removed; int /*<<< orphan*/  rcu_head; int /*<<< orphan*/  reorder_timer; int /*<<< orphan*/  reorder_lock; int /*<<< orphan*/  session_timer; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  agg_session_valid; int /*<<< orphan*/ * tid_rx; int /*<<< orphan*/  mtx; } ;
struct sta_info {TYPE_2__ sta; int /*<<< orphan*/  sdata; TYPE_1__ ampdu_mlme; struct ieee80211_local* local; } ;
struct ieee80211_local {int dummy; } ;
struct ieee80211_ampdu_params {size_t tid; int amsdu; int /*<<< orphan*/  ssn; int /*<<< orphan*/  timeout; int /*<<< orphan*/  action; TYPE_2__* sta; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_AMPDU_RX_STOP ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t WLAN_BACK_RECIPIENT ; 
 int /*<<< orphan*/  __clear_bit (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 scalar_t__ drv_ampdu_action (struct ieee80211_local*,int /*<<< orphan*/ ,struct ieee80211_ampdu_params*) ; 
 int /*<<< orphan*/  ht_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t,char*,int) ; 
 int /*<<< orphan*/  ieee80211_free_tid_rx ; 
 int /*<<< orphan*/  ieee80211_send_delba (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,size_t,size_t) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct tid_ampdu_rx* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdata_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (size_t,int /*<<< orphan*/ ) ; 

void ___ieee80211_stop_rx_ba_session(struct sta_info *sta, u16 tid,
				     u16 initiator, u16 reason, bool tx)
{
	struct ieee80211_local *local = sta->local;
	struct tid_ampdu_rx *tid_rx;
	struct ieee80211_ampdu_params params = {
		.sta = &sta->sta,
		.action = IEEE80211_AMPDU_RX_STOP,
		.tid = tid,
		.amsdu = false,
		.timeout = 0,
		.ssn = 0,
	};

	lockdep_assert_held(&sta->ampdu_mlme.mtx);

	tid_rx = rcu_dereference_protected(sta->ampdu_mlme.tid_rx[tid],
					lockdep_is_held(&sta->ampdu_mlme.mtx));

	if (!test_bit(tid, sta->ampdu_mlme.agg_session_valid))
		return;

	RCU_INIT_POINTER(sta->ampdu_mlme.tid_rx[tid], NULL);
	__clear_bit(tid, sta->ampdu_mlme.agg_session_valid);

	ht_dbg(sta->sdata,
	       "Rx BA session stop requested for %pM tid %u %s reason: %d\n",
	       sta->sta.addr, tid,
	       initiator == WLAN_BACK_RECIPIENT ? "recipient" : "initiator",
	       (int)reason);

	if (drv_ampdu_action(local, sta->sdata, &params))
		sdata_info(sta->sdata,
			   "HW problem - can not stop rx aggregation for %pM tid %d\n",
			   sta->sta.addr, tid);

	/* check if this is a self generated aggregation halt */
	if (initiator == WLAN_BACK_RECIPIENT && tx)
		ieee80211_send_delba(sta->sdata, sta->sta.addr,
				     tid, WLAN_BACK_RECIPIENT, reason);

	/*
	 * return here in case tid_rx is not assigned - which will happen if
	 * IEEE80211_HW_SUPPORTS_REORDERING_BUFFER is set.
	 */
	if (!tid_rx)
		return;

	del_timer_sync(&tid_rx->session_timer);

	/* make sure ieee80211_sta_reorder_release() doesn't re-arm the timer */
	spin_lock_bh(&tid_rx->reorder_lock);
	tid_rx->removed = true;
	spin_unlock_bh(&tid_rx->reorder_lock);
	del_timer_sync(&tid_rx->reorder_timer);

	call_rcu(&tid_rx->rcu_head, ieee80211_free_tid_rx);
}