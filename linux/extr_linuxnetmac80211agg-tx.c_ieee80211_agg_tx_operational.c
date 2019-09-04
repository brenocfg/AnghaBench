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
typedef  int /*<<< orphan*/  u16 ;
struct tid_ampdu_tx {int /*<<< orphan*/  state; int /*<<< orphan*/  amsdu; int /*<<< orphan*/  buf_size; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  mtx; } ;
struct sta_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  sdata; TYPE_2__ sta; TYPE_1__ ampdu_mlme; } ;
struct ieee80211_local {int dummy; } ;
struct ieee80211_ampdu_params {int /*<<< orphan*/  amsdu; int /*<<< orphan*/  buf_size; int /*<<< orphan*/  ssn; int /*<<< orphan*/  timeout; int /*<<< orphan*/  tid; int /*<<< orphan*/  action; TYPE_2__* sta; } ;

/* Variables and functions */
 int /*<<< orphan*/  HT_AGG_STATE_OPERATIONAL ; 
 int /*<<< orphan*/  IEEE80211_AMPDU_TX_OPERATIONAL ; 
 int /*<<< orphan*/  drv_ampdu_action (struct ieee80211_local*,int /*<<< orphan*/ ,struct ieee80211_ampdu_params*) ; 
 int /*<<< orphan*/  ht_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_agg_splice_finish (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_agg_splice_packets (int /*<<< orphan*/ ,struct tid_ampdu_tx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_agg_start_txq (struct sta_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 struct tid_ampdu_tx* rcu_dereference_protected_tid_tx (struct sta_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ieee80211_agg_tx_operational(struct ieee80211_local *local,
					 struct sta_info *sta, u16 tid)
{
	struct tid_ampdu_tx *tid_tx;
	struct ieee80211_ampdu_params params = {
		.sta = &sta->sta,
		.action = IEEE80211_AMPDU_TX_OPERATIONAL,
		.tid = tid,
		.timeout = 0,
		.ssn = 0,
	};

	lockdep_assert_held(&sta->ampdu_mlme.mtx);

	tid_tx = rcu_dereference_protected_tid_tx(sta, tid);
	params.buf_size = tid_tx->buf_size;
	params.amsdu = tid_tx->amsdu;

	ht_dbg(sta->sdata, "Aggregation is on for %pM tid %d\n",
	       sta->sta.addr, tid);

	drv_ampdu_action(local, sta->sdata, &params);

	/*
	 * synchronize with TX path, while splicing the TX path
	 * should block so it won't put more packets onto pending.
	 */
	spin_lock_bh(&sta->lock);

	ieee80211_agg_splice_packets(sta->sdata, tid_tx, tid);
	/*
	 * Now mark as operational. This will be visible
	 * in the TX path, and lets it go lock-free in
	 * the common case.
	 */
	set_bit(HT_AGG_STATE_OPERATIONAL, &tid_tx->state);
	ieee80211_agg_splice_finish(sta->sdata, tid);

	spin_unlock_bh(&sta->lock);

	ieee80211_agg_start_txq(sta, tid, true);
}