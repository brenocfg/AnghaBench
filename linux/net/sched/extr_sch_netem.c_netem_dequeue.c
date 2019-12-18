#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct sk_buff {int /*<<< orphan*/  dev; int /*<<< orphan*/ * prev; int /*<<< orphan*/ * next; } ;
struct TYPE_8__ {scalar_t__ slot_next; scalar_t__ packets_left; scalar_t__ bytes_left; } ;
struct netem_sched_data {TYPE_3__* qdisc; TYPE_1__ slot; int /*<<< orphan*/  watchdog; } ;
struct TYPE_12__ {int /*<<< orphan*/  qlen; } ;
struct Qdisc {TYPE_7__ q; } ;
struct TYPE_11__ {scalar_t__ time_to_send; } ;
struct TYPE_10__ {TYPE_2__* ops; } ;
struct TYPE_9__ {struct sk_buff* (* dequeue ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int NET_XMIT_SUCCESS ; 
 struct sk_buff* __qdisc_dequeue_head (TYPE_7__*) ; 
 int /*<<< orphan*/  get_slot_next (struct netem_sched_data*,scalar_t__) ; 
 int /*<<< orphan*/  kfree_skb_list (struct sk_buff*) ; 
 scalar_t__ ktime_get_ns () ; 
 int /*<<< orphan*/  max (scalar_t__,scalar_t__) ; 
 scalar_t__ net_xmit_drop_count (int) ; 
 int /*<<< orphan*/  netem_erase_head (struct netem_sched_data*,struct sk_buff*) ; 
 struct sk_buff* netem_peek (struct netem_sched_data*) ; 
 TYPE_6__* netem_skb_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  qdisc_bstats_update (struct Qdisc*,struct sk_buff*) ; 
 int /*<<< orphan*/  qdisc_dev (struct Qdisc*) ; 
 int qdisc_enqueue (struct sk_buff*,TYPE_3__*,struct sk_buff**) ; 
 unsigned int qdisc_pkt_len (struct sk_buff*) ; 
 struct netem_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_qstats_backlog_dec (struct Qdisc*,struct sk_buff*) ; 
 int /*<<< orphan*/  qdisc_qstats_drop (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_tree_reduce_backlog (struct Qdisc*,int,unsigned int) ; 
 int /*<<< orphan*/  qdisc_watchdog_schedule_ns (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct sk_buff* stub1 (TYPE_3__*) ; 
 struct sk_buff* stub2 (TYPE_3__*) ; 

__attribute__((used)) static struct sk_buff *netem_dequeue(struct Qdisc *sch)
{
	struct netem_sched_data *q = qdisc_priv(sch);
	struct sk_buff *skb;

tfifo_dequeue:
	skb = __qdisc_dequeue_head(&sch->q);
	if (skb) {
		qdisc_qstats_backlog_dec(sch, skb);
deliver:
		qdisc_bstats_update(sch, skb);
		return skb;
	}
	skb = netem_peek(q);
	if (skb) {
		u64 time_to_send;
		u64 now = ktime_get_ns();

		/* if more time remaining? */
		time_to_send = netem_skb_cb(skb)->time_to_send;
		if (q->slot.slot_next && q->slot.slot_next < time_to_send)
			get_slot_next(q, now);

		if (time_to_send <= now && q->slot.slot_next <= now) {
			netem_erase_head(q, skb);
			sch->q.qlen--;
			qdisc_qstats_backlog_dec(sch, skb);
			skb->next = NULL;
			skb->prev = NULL;
			/* skb->dev shares skb->rbnode area,
			 * we need to restore its value.
			 */
			skb->dev = qdisc_dev(sch);

			if (q->slot.slot_next) {
				q->slot.packets_left--;
				q->slot.bytes_left -= qdisc_pkt_len(skb);
				if (q->slot.packets_left <= 0 ||
				    q->slot.bytes_left <= 0)
					get_slot_next(q, now);
			}

			if (q->qdisc) {
				unsigned int pkt_len = qdisc_pkt_len(skb);
				struct sk_buff *to_free = NULL;
				int err;

				err = qdisc_enqueue(skb, q->qdisc, &to_free);
				kfree_skb_list(to_free);
				if (err != NET_XMIT_SUCCESS &&
				    net_xmit_drop_count(err)) {
					qdisc_qstats_drop(sch);
					qdisc_tree_reduce_backlog(sch, 1,
								  pkt_len);
				}
				goto tfifo_dequeue;
			}
			goto deliver;
		}

		if (q->qdisc) {
			skb = q->qdisc->ops->dequeue(q->qdisc);
			if (skb)
				goto deliver;
		}

		qdisc_watchdog_schedule_ns(&q->watchdog,
					   max(time_to_send,
					       q->slot.slot_next));
	}

	if (q->qdisc) {
		skb = q->qdisc->ops->dequeue(q->qdisc);
		if (skb)
			goto deliver;
	}
	return NULL;
}