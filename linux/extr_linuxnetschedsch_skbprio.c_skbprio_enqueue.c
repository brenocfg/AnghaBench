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
typedef  size_t u16 ;
struct skbprio_sched_data {size_t highest_prio; size_t lowest_prio; TYPE_1__* qstats; struct sk_buff_head* qdiscs; } ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  priority; } ;
struct TYPE_4__ {int qlen; } ;
struct Qdisc {int limit; TYPE_2__ q; } ;
struct TYPE_3__ {int /*<<< orphan*/  overlimits; int /*<<< orphan*/  drops; int /*<<< orphan*/  backlog; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int NET_XMIT_CN ; 
 int NET_XMIT_SUCCESS ; 
 int SKBPRIO_MAX_PRIORITY ; 
 struct sk_buff* __skb_dequeue_tail (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 size_t calc_new_low_prio (struct skbprio_sched_data*) ; 
 size_t min (int /*<<< orphan*/ ,unsigned int const) ; 
 int qdisc_drop (struct sk_buff*,struct Qdisc*,struct sk_buff**) ; 
 scalar_t__ qdisc_pkt_len (struct sk_buff*) ; 
 struct skbprio_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_qstats_backlog_dec (struct Qdisc*,struct sk_buff*) ; 
 int /*<<< orphan*/  qdisc_qstats_backlog_inc (struct Qdisc*,struct sk_buff*) ; 
 scalar_t__ skb_queue_empty (struct sk_buff_head*) ; 

__attribute__((used)) static int skbprio_enqueue(struct sk_buff *skb, struct Qdisc *sch,
			  struct sk_buff **to_free)
{
	const unsigned int max_priority = SKBPRIO_MAX_PRIORITY - 1;
	struct skbprio_sched_data *q = qdisc_priv(sch);
	struct sk_buff_head *qdisc;
	struct sk_buff_head *lp_qdisc;
	struct sk_buff *to_drop;
	u16 prio, lp;

	/* Obtain the priority of @skb. */
	prio = min(skb->priority, max_priority);

	qdisc = &q->qdiscs[prio];
	if (sch->q.qlen < sch->limit) {
		__skb_queue_tail(qdisc, skb);
		qdisc_qstats_backlog_inc(sch, skb);
		q->qstats[prio].backlog += qdisc_pkt_len(skb);

		/* Check to update highest and lowest priorities. */
		if (prio > q->highest_prio)
			q->highest_prio = prio;

		if (prio < q->lowest_prio)
			q->lowest_prio = prio;

		sch->q.qlen++;
		return NET_XMIT_SUCCESS;
	}

	/* If this packet has the lowest priority, drop it. */
	lp = q->lowest_prio;
	if (prio <= lp) {
		q->qstats[prio].drops++;
		q->qstats[prio].overlimits++;
		return qdisc_drop(skb, sch, to_free);
	}

	__skb_queue_tail(qdisc, skb);
	qdisc_qstats_backlog_inc(sch, skb);
	q->qstats[prio].backlog += qdisc_pkt_len(skb);

	/* Drop the packet at the tail of the lowest priority qdisc. */
	lp_qdisc = &q->qdiscs[lp];
	to_drop = __skb_dequeue_tail(lp_qdisc);
	BUG_ON(!to_drop);
	qdisc_qstats_backlog_dec(sch, to_drop);
	qdisc_drop(to_drop, sch, to_free);

	q->qstats[lp].backlog -= qdisc_pkt_len(to_drop);
	q->qstats[lp].drops++;
	q->qstats[lp].overlimits++;

	/* Check to update highest and lowest priorities. */
	if (skb_queue_empty(lp_qdisc)) {
		if (q->lowest_prio == q->highest_prio) {
			/* The incoming packet is the only packet in queue. */
			BUG_ON(sch->q.qlen != 1);
			q->lowest_prio = prio;
			q->highest_prio = prio;
		} else {
			q->lowest_prio = calc_new_low_prio(q);
		}
	}

	if (prio > q->highest_prio)
		q->highest_prio = prio;

	return NET_XMIT_CN;
}