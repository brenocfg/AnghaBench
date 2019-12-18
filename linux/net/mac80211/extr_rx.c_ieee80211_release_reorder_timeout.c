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
struct tid_ampdu_rx {int /*<<< orphan*/  reorder_lock; } ;
struct TYPE_4__ {int /*<<< orphan*/ * tid_rx; } ;
struct sta_info {int /*<<< orphan*/  sta; int /*<<< orphan*/  sdata; TYPE_1__ ampdu_mlme; int /*<<< orphan*/  local; } ;
struct sk_buff_head {int dummy; } ;
struct ieee80211_rx_data {int security_idx; int seqno_idx; int /*<<< orphan*/  sdata; int /*<<< orphan*/  local; int /*<<< orphan*/ * napi; struct sta_info* sta; } ;
struct TYPE_5__ {int tid; int /*<<< orphan*/ * sta; } ;
struct TYPE_6__ {TYPE_2__ ba; } ;
struct ieee80211_event {TYPE_3__ u; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BA_FRAME_TIMEOUT ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  drv_event_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee80211_event*) ; 
 int /*<<< orphan*/  ieee80211_rx_handlers (struct ieee80211_rx_data*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  ieee80211_sta_reorder_release (int /*<<< orphan*/ ,struct tid_ampdu_rx*,struct sk_buff_head*) ; 
 struct tid_ampdu_rx* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_empty (struct sk_buff_head*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void ieee80211_release_reorder_timeout(struct sta_info *sta, int tid)
{
	struct sk_buff_head frames;
	struct ieee80211_rx_data rx = {
		.sta = sta,
		.sdata = sta->sdata,
		.local = sta->local,
		/* This is OK -- must be QoS data frame */
		.security_idx = tid,
		.seqno_idx = tid,
		.napi = NULL, /* must be NULL to not have races */
	};
	struct tid_ampdu_rx *tid_agg_rx;

	tid_agg_rx = rcu_dereference(sta->ampdu_mlme.tid_rx[tid]);
	if (!tid_agg_rx)
		return;

	__skb_queue_head_init(&frames);

	spin_lock(&tid_agg_rx->reorder_lock);
	ieee80211_sta_reorder_release(sta->sdata, tid_agg_rx, &frames);
	spin_unlock(&tid_agg_rx->reorder_lock);

	if (!skb_queue_empty(&frames)) {
		struct ieee80211_event event = {
			.type = BA_FRAME_TIMEOUT,
			.u.ba.tid = tid,
			.u.ba.sta = &sta->sta,
		};
		drv_event_callback(rx.local, rx.sdata, &event);
	}

	ieee80211_rx_handlers(&rx, &frames);
}