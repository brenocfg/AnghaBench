#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wireless_dev {int dummy; } ;
struct wiphy {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  txq; } ;
struct ieee80211_sub_if_data {TYPE_2__ vif; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  flows_cnt; int /*<<< orphan*/  collisions; int /*<<< orphan*/  overmemory; int /*<<< orphan*/  overlimit; int /*<<< orphan*/  memory_usage; int /*<<< orphan*/  backlog; } ;
struct ieee80211_local {TYPE_3__ fq; TYPE_1__* ops; } ;
struct cfg80211_txq_stats {int filled; int /*<<< orphan*/  max_flows; int /*<<< orphan*/  collisions; int /*<<< orphan*/  overmemory; int /*<<< orphan*/  overlimit; int /*<<< orphan*/  backlog_bytes; int /*<<< orphan*/  backlog_packets; } ;
struct TYPE_4__ {int /*<<< orphan*/  wake_tx_queue; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 struct ieee80211_sub_if_data* IEEE80211_WDEV_TO_SUB_IF (struct wireless_dev*) ; 
 int /*<<< orphan*/  NL80211_TXQ_STATS_BACKLOG_BYTES ; 
 int /*<<< orphan*/  NL80211_TXQ_STATS_BACKLOG_PACKETS ; 
 int /*<<< orphan*/  NL80211_TXQ_STATS_COLLISIONS ; 
 int /*<<< orphan*/  NL80211_TXQ_STATS_MAX_FLOWS ; 
 int /*<<< orphan*/  NL80211_TXQ_STATS_OVERLIMIT ; 
 int /*<<< orphan*/  NL80211_TXQ_STATS_OVERMEMORY ; 
 int /*<<< orphan*/  ieee80211_fill_txq_stats (struct cfg80211_txq_stats*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_txq_info (int /*<<< orphan*/ ) ; 
 struct ieee80211_local* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int ieee80211_get_txq_stats(struct wiphy *wiphy,
				   struct wireless_dev *wdev,
				   struct cfg80211_txq_stats *txqstats)
{
	struct ieee80211_local *local = wiphy_priv(wiphy);
	struct ieee80211_sub_if_data *sdata;
	int ret = 0;

	if (!local->ops->wake_tx_queue)
		return 1;

	spin_lock_bh(&local->fq.lock);
	rcu_read_lock();

	if (wdev) {
		sdata = IEEE80211_WDEV_TO_SUB_IF(wdev);
		if (!sdata->vif.txq) {
			ret = 1;
			goto out;
		}
		ieee80211_fill_txq_stats(txqstats, to_txq_info(sdata->vif.txq));
	} else {
		/* phy stats */
		txqstats->filled |= BIT(NL80211_TXQ_STATS_BACKLOG_PACKETS) |
				    BIT(NL80211_TXQ_STATS_BACKLOG_BYTES) |
				    BIT(NL80211_TXQ_STATS_OVERLIMIT) |
				    BIT(NL80211_TXQ_STATS_OVERMEMORY) |
				    BIT(NL80211_TXQ_STATS_COLLISIONS) |
				    BIT(NL80211_TXQ_STATS_MAX_FLOWS);
		txqstats->backlog_packets = local->fq.backlog;
		txqstats->backlog_bytes = local->fq.memory_usage;
		txqstats->overlimit = local->fq.overlimit;
		txqstats->overmemory = local->fq.overmemory;
		txqstats->collisions = local->fq.collisions;
		txqstats->max_flows = local->fq.flows_cnt;
	}

out:
	rcu_read_unlock();
	spin_unlock_bh(&local->fq.lock);

	return ret;
}