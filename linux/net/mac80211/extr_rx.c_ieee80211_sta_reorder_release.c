#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tid_ampdu_rx {int head_seq_num; int buf_size; int /*<<< orphan*/  reorder_timer; scalar_t__* reorder_time; int /*<<< orphan*/  removed; scalar_t__ stored_mpdu_num; int /*<<< orphan*/ * reorder_buf; int /*<<< orphan*/  reorder_lock; } ;
struct sk_buff_head {int dummy; } ;
struct ieee80211_sub_if_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ HT_RX_REORDER_BUF_TIMEOUT ; 
 int IEEE80211_SN_MASK ; 
 int /*<<< orphan*/  __skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ht_dbg_ratelimited (struct ieee80211_sub_if_data*,char*) ; 
 int /*<<< orphan*/  ieee80211_release_reorder_frame (struct ieee80211_sub_if_data*,struct tid_ampdu_rx*,int,struct sk_buff_head*) ; 
 scalar_t__ ieee80211_rx_reorder_ready (struct tid_ampdu_rx*,int) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  time_after (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ieee80211_sta_reorder_release(struct ieee80211_sub_if_data *sdata,
					  struct tid_ampdu_rx *tid_agg_rx,
					  struct sk_buff_head *frames)
{
	int index, i, j;

	lockdep_assert_held(&tid_agg_rx->reorder_lock);

	/* release the buffer until next missing frame */
	index = tid_agg_rx->head_seq_num % tid_agg_rx->buf_size;
	if (!ieee80211_rx_reorder_ready(tid_agg_rx, index) &&
	    tid_agg_rx->stored_mpdu_num) {
		/*
		 * No buffers ready to be released, but check whether any
		 * frames in the reorder buffer have timed out.
		 */
		int skipped = 1;
		for (j = (index + 1) % tid_agg_rx->buf_size; j != index;
		     j = (j + 1) % tid_agg_rx->buf_size) {
			if (!ieee80211_rx_reorder_ready(tid_agg_rx, j)) {
				skipped++;
				continue;
			}
			if (skipped &&
			    !time_after(jiffies, tid_agg_rx->reorder_time[j] +
					HT_RX_REORDER_BUF_TIMEOUT))
				goto set_release_timer;

			/* don't leave incomplete A-MSDUs around */
			for (i = (index + 1) % tid_agg_rx->buf_size; i != j;
			     i = (i + 1) % tid_agg_rx->buf_size)
				__skb_queue_purge(&tid_agg_rx->reorder_buf[i]);

			ht_dbg_ratelimited(sdata,
					   "release an RX reorder frame due to timeout on earlier frames\n");
			ieee80211_release_reorder_frame(sdata, tid_agg_rx, j,
							frames);

			/*
			 * Increment the head seq# also for the skipped slots.
			 */
			tid_agg_rx->head_seq_num =
				(tid_agg_rx->head_seq_num +
				 skipped) & IEEE80211_SN_MASK;
			skipped = 0;
		}
	} else while (ieee80211_rx_reorder_ready(tid_agg_rx, index)) {
		ieee80211_release_reorder_frame(sdata, tid_agg_rx, index,
						frames);
		index =	tid_agg_rx->head_seq_num % tid_agg_rx->buf_size;
	}

	if (tid_agg_rx->stored_mpdu_num) {
		j = index = tid_agg_rx->head_seq_num % tid_agg_rx->buf_size;

		for (; j != (index - 1) % tid_agg_rx->buf_size;
		     j = (j + 1) % tid_agg_rx->buf_size) {
			if (ieee80211_rx_reorder_ready(tid_agg_rx, j))
				break;
		}

 set_release_timer:

		if (!tid_agg_rx->removed)
			mod_timer(&tid_agg_rx->reorder_timer,
				  tid_agg_rx->reorder_time[j] + 1 +
				  HT_RX_REORDER_BUF_TIMEOUT);
	} else {
		del_timer(&tid_agg_rx->reorder_timer);
	}
}