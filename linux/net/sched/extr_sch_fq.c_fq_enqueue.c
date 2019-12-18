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
struct sock {int /*<<< orphan*/  sk_pacing_status; } ;
struct sk_buff {struct sock* sk; } ;
struct fq_flow {scalar_t__ qlen; int /*<<< orphan*/  credit; scalar_t__ age; } ;
struct fq_sched_data {scalar_t__ flow_plimit; int /*<<< orphan*/  stat_internal_packets; struct fq_flow internal; int /*<<< orphan*/  inactive_flows; scalar_t__ rate_enable; int /*<<< orphan*/  quantum; scalar_t__ flow_refill_delay; int /*<<< orphan*/  new_flows; int /*<<< orphan*/  stat_flows_plimit; } ;
struct TYPE_2__ {scalar_t__ qlen; } ;
struct Qdisc {scalar_t__ limit; TYPE_1__ q; } ;

/* Variables and functions */
 int NET_XMIT_SUCCESS ; 
 scalar_t__ SK_PACING_FQ ; 
 int /*<<< orphan*/  flow_queue_add (struct fq_flow*,struct sk_buff*) ; 
 struct fq_flow* fq_classify (struct sk_buff*,struct fq_sched_data*) ; 
 int /*<<< orphan*/  fq_flow_add_tail (int /*<<< orphan*/ *,struct fq_flow*) ; 
 scalar_t__ fq_flow_is_detached (struct fq_flow*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  max_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qdisc_drop (struct sk_buff*,struct Qdisc*,struct sk_buff**) ; 
 struct fq_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_qstats_backlog_inc (struct Qdisc*,struct sk_buff*) ; 
 scalar_t__ smp_load_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_store_release (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  u32 ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int fq_enqueue(struct sk_buff *skb, struct Qdisc *sch,
		      struct sk_buff **to_free)
{
	struct fq_sched_data *q = qdisc_priv(sch);
	struct fq_flow *f;

	if (unlikely(sch->q.qlen >= sch->limit))
		return qdisc_drop(skb, sch, to_free);

	f = fq_classify(skb, q);
	if (unlikely(f->qlen >= q->flow_plimit && f != &q->internal)) {
		q->stat_flows_plimit++;
		return qdisc_drop(skb, sch, to_free);
	}

	f->qlen++;
	qdisc_qstats_backlog_inc(sch, skb);
	if (fq_flow_is_detached(f)) {
		struct sock *sk = skb->sk;

		fq_flow_add_tail(&q->new_flows, f);
		if (time_after(jiffies, f->age + q->flow_refill_delay))
			f->credit = max_t(u32, f->credit, q->quantum);
		if (sk && q->rate_enable) {
			if (unlikely(smp_load_acquire(&sk->sk_pacing_status) !=
				     SK_PACING_FQ))
				smp_store_release(&sk->sk_pacing_status,
						  SK_PACING_FQ);
		}
		q->inactive_flows--;
	}

	/* Note: this overwrites f->age */
	flow_queue_add(f, skb);

	if (unlikely(f == &q->internal)) {
		q->stat_internal_packets++;
	}
	sch->q.qlen++;

	return NET_XMIT_SUCCESS;
}