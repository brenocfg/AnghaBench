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
typedef  int /*<<< orphan*/  u16 ;
struct tid_ampdu_rx {int head_seq_num; int buf_size; int /*<<< orphan*/  reorder_lock; } ;
struct sk_buff_head {int dummy; } ;
struct ieee80211_sub_if_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_release_reorder_frame (struct ieee80211_sub_if_data*,struct tid_ampdu_rx*,int,struct sk_buff_head*) ; 
 scalar_t__ ieee80211_sn_less (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ieee80211_release_reorder_frames(struct ieee80211_sub_if_data *sdata,
					     struct tid_ampdu_rx *tid_agg_rx,
					     u16 head_seq_num,
					     struct sk_buff_head *frames)
{
	int index;

	lockdep_assert_held(&tid_agg_rx->reorder_lock);

	while (ieee80211_sn_less(tid_agg_rx->head_seq_num, head_seq_num)) {
		index = tid_agg_rx->head_seq_num % tid_agg_rx->buf_size;
		ieee80211_release_reorder_frame(sdata, tid_agg_rx, index,
						frames);
	}
}