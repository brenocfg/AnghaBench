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
typedef  scalar_t__ u32 ;
struct sk_buff {scalar_t__ truesize; } ;
struct cake_tin_data {int /*<<< orphan*/ * overflow_idx; int /*<<< orphan*/  tin_backlog; int /*<<< orphan*/ * backlogs; struct cake_flow* flows; } ;
struct cake_sched_data {size_t cur_tin; size_t cur_flow; scalar_t__ overflow_timeout; int /*<<< orphan*/  buffer_used; struct cake_tin_data* tins; } ;
struct cake_flow {scalar_t__ head; } ;
struct TYPE_4__ {int /*<<< orphan*/  qlen; } ;
struct TYPE_3__ {int /*<<< orphan*/  backlog; } ;
struct Qdisc {TYPE_2__ q; TYPE_1__ qstats; } ;

/* Variables and functions */
 int /*<<< orphan*/  cake_heapify (struct cake_sched_data*,int /*<<< orphan*/ ) ; 
 struct sk_buff* dequeue_head (struct cake_flow*) ; 
 scalar_t__ qdisc_pkt_len (struct sk_buff*) ; 
 struct cake_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static struct sk_buff *cake_dequeue_one(struct Qdisc *sch)
{
	struct cake_sched_data *q = qdisc_priv(sch);
	struct cake_tin_data *b = &q->tins[q->cur_tin];
	struct cake_flow *flow = &b->flows[q->cur_flow];
	struct sk_buff *skb = NULL;
	u32 len;

	if (flow->head) {
		skb = dequeue_head(flow);
		len = qdisc_pkt_len(skb);
		b->backlogs[q->cur_flow] -= len;
		b->tin_backlog		 -= len;
		sch->qstats.backlog      -= len;
		q->buffer_used		 -= skb->truesize;
		sch->q.qlen--;

		if (q->overflow_timeout)
			cake_heapify(q, b->overflow_idx[q->cur_flow]);
	}
	return skb;
}