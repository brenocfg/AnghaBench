#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * txq; } ;
struct TYPE_9__ {int /*<<< orphan*/ * msdu_failed; int /*<<< orphan*/ * msdu_retries; } ;
struct TYPE_8__ {int /*<<< orphan*/ * msdu; } ;
struct TYPE_7__ {int /*<<< orphan*/ * msdu; int /*<<< orphan*/  syncp; } ;
struct sta_info {TYPE_5__ sta; TYPE_3__ status_stats; TYPE_2__ tx_stats; TYPE_1__ rx_stats; struct ieee80211_local* local; } ;
struct TYPE_12__ {int /*<<< orphan*/  lock; } ;
struct ieee80211_local {TYPE_6__ fq; TYPE_4__* ops; int /*<<< orphan*/  hw; } ;
struct cfg80211_tid_stats {int filled; int /*<<< orphan*/  txq_stats; int /*<<< orphan*/  tx_msdu_failed; int /*<<< orphan*/  tx_msdu_retries; int /*<<< orphan*/  tx_msdu; int /*<<< orphan*/  rx_msdu; } ;
struct TYPE_10__ {scalar_t__ wake_tx_queue; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int IEEE80211_NUM_TIDS ; 
 int /*<<< orphan*/  NL80211_TID_STATS_RX_MSDU ; 
 int /*<<< orphan*/  NL80211_TID_STATS_TXQ_STATS ; 
 int /*<<< orphan*/  NL80211_TID_STATS_TX_MSDU ; 
 int /*<<< orphan*/  NL80211_TID_STATS_TX_MSDU_FAILED ; 
 int /*<<< orphan*/  NL80211_TID_STATS_TX_MSDU_RETRIES ; 
 int /*<<< orphan*/  REPORTS_TX_ACK_STATUS ; 
 int /*<<< orphan*/  ieee80211_fill_txq_stats (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_hw_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_txq_info (int /*<<< orphan*/ ) ; 
 unsigned int u64_stats_fetch_begin (int /*<<< orphan*/ *) ; 
 scalar_t__ u64_stats_fetch_retry (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void sta_set_tidstats(struct sta_info *sta,
			     struct cfg80211_tid_stats *tidstats,
			     int tid)
{
	struct ieee80211_local *local = sta->local;

	if (!(tidstats->filled & BIT(NL80211_TID_STATS_RX_MSDU))) {
		unsigned int start;

		do {
			start = u64_stats_fetch_begin(&sta->rx_stats.syncp);
			tidstats->rx_msdu = sta->rx_stats.msdu[tid];
		} while (u64_stats_fetch_retry(&sta->rx_stats.syncp, start));

		tidstats->filled |= BIT(NL80211_TID_STATS_RX_MSDU);
	}

	if (!(tidstats->filled & BIT(NL80211_TID_STATS_TX_MSDU))) {
		tidstats->filled |= BIT(NL80211_TID_STATS_TX_MSDU);
		tidstats->tx_msdu = sta->tx_stats.msdu[tid];
	}

	if (!(tidstats->filled & BIT(NL80211_TID_STATS_TX_MSDU_RETRIES)) &&
	    ieee80211_hw_check(&local->hw, REPORTS_TX_ACK_STATUS)) {
		tidstats->filled |= BIT(NL80211_TID_STATS_TX_MSDU_RETRIES);
		tidstats->tx_msdu_retries = sta->status_stats.msdu_retries[tid];
	}

	if (!(tidstats->filled & BIT(NL80211_TID_STATS_TX_MSDU_FAILED)) &&
	    ieee80211_hw_check(&local->hw, REPORTS_TX_ACK_STATUS)) {
		tidstats->filled |= BIT(NL80211_TID_STATS_TX_MSDU_FAILED);
		tidstats->tx_msdu_failed = sta->status_stats.msdu_failed[tid];
	}

	if (local->ops->wake_tx_queue && tid < IEEE80211_NUM_TIDS) {
		spin_lock_bh(&local->fq.lock);
		rcu_read_lock();

		tidstats->filled |= BIT(NL80211_TID_STATS_TXQ_STATS);
		ieee80211_fill_txq_stats(&tidstats->txq_stats,
					 to_txq_info(sta->sta.txq[tid]));

		rcu_read_unlock();
		spin_unlock_bh(&local->fq.lock);
	}
}