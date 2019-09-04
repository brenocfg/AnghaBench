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
struct sk_buff {int dummy; } ;
struct ieee80211_tx_info {scalar_t__ rate_driver_data; } ;
struct carl9170_tx_info {scalar_t__ timeout; } ;
struct ar9170 {TYPE_2__* tx_status; TYPE_1__* hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARL9170_QUEUE_STUCK_TIMEOUT ; 
 int /*<<< orphan*/  CARL9170_RR_STUCK_TX ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  carl9170_restart (struct ar9170*,int /*<<< orphan*/ ) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_peek (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int time_is_before_jiffies (scalar_t__) ; 

__attribute__((used)) static void carl9170_check_queue_stop_timeout(struct ar9170 *ar)
{
	int i;
	struct sk_buff *skb;
	struct ieee80211_tx_info *txinfo;
	struct carl9170_tx_info *arinfo;
	bool restart = false;

	for (i = 0; i < ar->hw->queues; i++) {
		spin_lock_bh(&ar->tx_status[i].lock);

		skb = skb_peek(&ar->tx_status[i]);

		if (!skb)
			goto next;

		txinfo = IEEE80211_SKB_CB(skb);
		arinfo = (void *) txinfo->rate_driver_data;

		if (time_is_before_jiffies(arinfo->timeout +
		    msecs_to_jiffies(CARL9170_QUEUE_STUCK_TIMEOUT)) == true)
			restart = true;

next:
		spin_unlock_bh(&ar->tx_status[i].lock);
	}

	if (restart) {
		/*
		 * At least one queue has been stuck for long enough.
		 * Give the device a kick and hope it gets back to
		 * work.
		 *
		 * possible reasons may include:
		 *  - frames got lost/corrupted (bad connection to the device)
		 *  - stalled rx processing/usb controller hiccups
		 *  - firmware errors/bugs
		 *  - every bug you can think of.
		 *  - all bugs you can't...
		 *  - ...
		 */
		carl9170_restart(ar, CARL9170_RR_STUCK_TX);
	}
}