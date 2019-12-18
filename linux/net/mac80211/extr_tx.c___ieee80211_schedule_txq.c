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
struct TYPE_5__ {scalar_t__ sta; } ;
struct TYPE_4__ {scalar_t__ backlog_packets; } ;
struct txq_info {int /*<<< orphan*/  schedule_order; TYPE_2__ txq; TYPE_1__ tin; int /*<<< orphan*/  frags; } ;
struct ieee80211_txq {size_t ac; } ;
struct TYPE_6__ {int /*<<< orphan*/  wiphy; } ;
struct ieee80211_local {int /*<<< orphan*/ * active_txq_lock; int /*<<< orphan*/ * active_txqs; TYPE_3__ hw; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL80211_EXT_FEATURE_AIRTIME_FAIRNESS ; 
 struct ieee80211_local* hw_to_local (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct txq_info* to_txq_info (struct ieee80211_txq*) ; 
 scalar_t__ wiphy_ext_feature_isset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void __ieee80211_schedule_txq(struct ieee80211_hw *hw,
			      struct ieee80211_txq *txq,
			      bool force)
{
	struct ieee80211_local *local = hw_to_local(hw);
	struct txq_info *txqi = to_txq_info(txq);

	spin_lock_bh(&local->active_txq_lock[txq->ac]);

	if (list_empty(&txqi->schedule_order) &&
	    (force || !skb_queue_empty(&txqi->frags) ||
	     txqi->tin.backlog_packets)) {
		/* If airtime accounting is active, always enqueue STAs at the
		 * head of the list to ensure that they only get moved to the
		 * back by the airtime DRR scheduler once they have a negative
		 * deficit. A station that already has a negative deficit will
		 * get immediately moved to the back of the list on the next
		 * call to ieee80211_next_txq().
		 */
		if (txqi->txq.sta &&
		    wiphy_ext_feature_isset(local->hw.wiphy,
					    NL80211_EXT_FEATURE_AIRTIME_FAIRNESS))
			list_add(&txqi->schedule_order,
				 &local->active_txqs[txq->ac]);
		else
			list_add_tail(&txqi->schedule_order,
				      &local->active_txqs[txq->ac]);
	}

	spin_unlock_bh(&local->active_txq_lock[txq->ac]);
}