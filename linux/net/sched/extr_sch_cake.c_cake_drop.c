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
typedef  size_t u32 ;
struct sk_buff {scalar_t__ truesize; } ;
struct cake_tin_data {int /*<<< orphan*/  tin_dropped; int /*<<< orphan*/  tin_backlog; int /*<<< orphan*/ * backlogs; int /*<<< orphan*/  unresponsive_flow_count; int /*<<< orphan*/  cparams; struct cake_flow* flows; } ;
struct cake_sched_data {int overflow_timeout; int rate_flags; int /*<<< orphan*/  buffer_used; struct cake_tin_data* tins; struct cake_heap_entry* overflow_heap; } ;
struct cake_heap_entry {size_t t; size_t b; } ;
struct cake_flow {int /*<<< orphan*/  dropped; int /*<<< orphan*/  cvars; } ;
struct TYPE_4__ {int /*<<< orphan*/  qlen; } ;
struct TYPE_3__ {int /*<<< orphan*/  drops; int /*<<< orphan*/  backlog; } ;
struct Qdisc {TYPE_2__ q; TYPE_1__ qstats; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int CAKE_FLAG_INGRESS ; 
 int CAKE_MAX_TINS ; 
 int CAKE_QUEUES ; 
 int /*<<< orphan*/  __qdisc_drop (struct sk_buff*,struct sk_buff**) ; 
 int /*<<< orphan*/  cake_advance_shaper (struct cake_sched_data*,struct cake_tin_data*,struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cake_heapify (struct cake_sched_data*,int) ; 
 scalar_t__ cobalt_queue_full (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct sk_buff* dequeue_head (struct cake_flow*) ; 
 int /*<<< orphan*/  ktime_get () ; 
 size_t qdisc_pkt_len (struct sk_buff*) ; 
 struct cake_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_tree_reduce_backlog (struct Qdisc*,int,size_t) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned int cake_drop(struct Qdisc *sch, struct sk_buff **to_free)
{
	struct cake_sched_data *q = qdisc_priv(sch);
	ktime_t now = ktime_get();
	u32 idx = 0, tin = 0, len;
	struct cake_heap_entry qq;
	struct cake_tin_data *b;
	struct cake_flow *flow;
	struct sk_buff *skb;

	if (!q->overflow_timeout) {
		int i;
		/* Build fresh max-heap */
		for (i = CAKE_MAX_TINS * CAKE_QUEUES / 2; i >= 0; i--)
			cake_heapify(q, i);
	}
	q->overflow_timeout = 65535;

	/* select longest queue for pruning */
	qq  = q->overflow_heap[0];
	tin = qq.t;
	idx = qq.b;

	b = &q->tins[tin];
	flow = &b->flows[idx];
	skb = dequeue_head(flow);
	if (unlikely(!skb)) {
		/* heap has gone wrong, rebuild it next time */
		q->overflow_timeout = 0;
		return idx + (tin << 16);
	}

	if (cobalt_queue_full(&flow->cvars, &b->cparams, now))
		b->unresponsive_flow_count++;

	len = qdisc_pkt_len(skb);
	q->buffer_used      -= skb->truesize;
	b->backlogs[idx]    -= len;
	b->tin_backlog      -= len;
	sch->qstats.backlog -= len;
	qdisc_tree_reduce_backlog(sch, 1, len);

	flow->dropped++;
	b->tin_dropped++;
	sch->qstats.drops++;

	if (q->rate_flags & CAKE_FLAG_INGRESS)
		cake_advance_shaper(q, b, skb, now, true);

	__qdisc_drop(skb, to_free);
	sch->q.qlen--;

	cake_heapify(q, 0);

	return idx + (tin << 16);
}