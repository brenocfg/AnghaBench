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
struct sk_buff {int dummy; } ;
struct ieee80211_tx_info {int flags; } ;
struct ar9170 {int /*<<< orphan*/  tx_flush; int /*<<< orphan*/  tx_total_queued; int /*<<< orphan*/  tx_ampdu_upload; int /*<<< orphan*/ * tx_pending; TYPE_1__* hw; } ;
struct TYPE_2__ {int queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_AMPDU ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  carl9170_tx_status (struct ar9170*,struct sk_buff*,int) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 scalar_t__ wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void carl9170_flush(struct ar9170 *ar, bool drop_queued)
{
	if (drop_queued) {
		int i;

		/*
		 * We can only drop frames which have not been uploaded
		 * to the device yet.
		 */

		for (i = 0; i < ar->hw->queues; i++) {
			struct sk_buff *skb;

			while ((skb = skb_dequeue(&ar->tx_pending[i]))) {
				struct ieee80211_tx_info *info;

				info = IEEE80211_SKB_CB(skb);
				if (info->flags & IEEE80211_TX_CTL_AMPDU)
					atomic_dec(&ar->tx_ampdu_upload);

				carl9170_tx_status(ar, skb, false);
			}
		}
	}

	/* Wait for all other outstanding frames to timeout. */
	if (atomic_read(&ar->tx_total_queued))
		WARN_ON(wait_for_completion_timeout(&ar->tx_flush, HZ) == 0);
}