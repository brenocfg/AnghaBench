#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct rt2x00_dev {TYPE_2__* ops; int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {TYPE_3__* rates; } ;
struct ieee80211_tx_info {int flags; TYPE_4__ control; } ;
struct ieee80211_tx_control {int /*<<< orphan*/  sta; } ;
struct ieee80211_hw {struct rt2x00_dev* priv; } ;
struct data_queue {int /*<<< orphan*/  tx_lock; } ;
typedef  enum data_queue_qid { ____Placeholder_data_queue_qid } data_queue_qid ;
struct TYPE_7__ {int flags; } ;
struct TYPE_6__ {TYPE_1__* hw; } ;
struct TYPE_5__ {int /*<<< orphan*/  set_rts_threshold; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_STATE_PRESENT ; 
 int /*<<< orphan*/  DRV_PROJECT ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_SEND_AFTER_DTIM ; 
 int IEEE80211_TX_RC_USE_CTS_PROTECT ; 
 int IEEE80211_TX_RC_USE_RTS_CTS ; 
 int QID_ATIM ; 
 int /*<<< orphan*/  REQUIRE_ATIM_QUEUE ; 
 int /*<<< orphan*/  ieee80211_free_txskb (struct ieee80211_hw*,struct sk_buff*) ; 
 int /*<<< orphan*/  rt2x00_err (struct rt2x00_dev*,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2x00_has_cap_flag (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2x00mac_tx_rts_cts (struct rt2x00_dev*,struct data_queue*,struct sk_buff*) ; 
 int rt2x00queue_available (struct data_queue*) ; 
 struct data_queue* rt2x00queue_get_tx_queue (struct rt2x00_dev*,int) ; 
 int /*<<< orphan*/  rt2x00queue_pause_queue (struct data_queue*) ; 
 scalar_t__ rt2x00queue_threshold (struct data_queue*) ; 
 int rt2x00queue_write_tx_frame (struct data_queue*,struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int skb_get_queue_mapping (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void rt2x00mac_tx(struct ieee80211_hw *hw,
		  struct ieee80211_tx_control *control,
		  struct sk_buff *skb)
{
	struct rt2x00_dev *rt2x00dev = hw->priv;
	struct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	enum data_queue_qid qid = skb_get_queue_mapping(skb);
	struct data_queue *queue = NULL;

	/*
	 * Mac80211 might be calling this function while we are trying
	 * to remove the device or perhaps suspending it.
	 * Note that we can only stop the TX queues inside the TX path
	 * due to possible race conditions in mac80211.
	 */
	if (!test_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags))
		goto exit_free_skb;

	/*
	 * Use the ATIM queue if appropriate and present.
	 */
	if (tx_info->flags & IEEE80211_TX_CTL_SEND_AFTER_DTIM &&
	    rt2x00_has_cap_flag(rt2x00dev, REQUIRE_ATIM_QUEUE))
		qid = QID_ATIM;

	queue = rt2x00queue_get_tx_queue(rt2x00dev, qid);
	if (unlikely(!queue)) {
		rt2x00_err(rt2x00dev,
			   "Attempt to send packet over invalid queue %d\n"
			   "Please file bug report to %s\n", qid, DRV_PROJECT);
		goto exit_free_skb;
	}

	/*
	 * If CTS/RTS is required. create and queue that frame first.
	 * Make sure we have at least enough entries available to send
	 * this CTS/RTS frame as well as the data frame.
	 * Note that when the driver has set the set_rts_threshold()
	 * callback function it doesn't need software generation of
	 * either RTS or CTS-to-self frame and handles everything
	 * inside the hardware.
	 */
	if (!rt2x00dev->ops->hw->set_rts_threshold &&
	    (tx_info->control.rates[0].flags & (IEEE80211_TX_RC_USE_RTS_CTS |
						IEEE80211_TX_RC_USE_CTS_PROTECT))) {
		if (rt2x00queue_available(queue) <= 1) {
			/*
			 * Recheck for full queue under lock to avoid race
			 * conditions with rt2x00lib_txdone().
			 */
			spin_lock(&queue->tx_lock);
			if (rt2x00queue_threshold(queue))
				rt2x00queue_pause_queue(queue);
			spin_unlock(&queue->tx_lock);

			goto exit_free_skb;
		}

		if (rt2x00mac_tx_rts_cts(rt2x00dev, queue, skb))
			goto exit_free_skb;
	}

	if (unlikely(rt2x00queue_write_tx_frame(queue, skb, control->sta, false)))
		goto exit_free_skb;

	return;

 exit_free_skb:
	ieee80211_free_txskb(hw, skb);
}