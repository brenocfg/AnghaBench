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
typedef  scalar_t__ u64 ;
typedef  unsigned int u32 ;
struct sk_buff {TYPE_1__* sk; int /*<<< orphan*/  end; } ;
struct fq_flow_head {struct fq_flow* first; } ;
struct fq_flow {scalar_t__ credit; scalar_t__ time_next_packet; struct fq_flow* next; struct sk_buff* head; } ;
struct fq_sched_data {unsigned long long time_next_delayed_flow; scalar_t__ quantum; unsigned int flow_max_rate; unsigned int low_rate_threshold; int /*<<< orphan*/  stat_pkts_too_long; int /*<<< orphan*/  rate_enable; int /*<<< orphan*/  inactive_flows; struct fq_flow_head old_flows; struct fq_flow_head new_flows; int /*<<< orphan*/  watchdog; struct fq_flow internal; } ;
struct Qdisc {int dummy; } ;
struct TYPE_2__ {scalar_t__ sk_pacing_rate; } ;

/* Variables and functions */
 scalar_t__ NSEC_PER_SEC ; 
 int /*<<< orphan*/  do_div (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  fq_check_throttled (struct fq_sched_data*,scalar_t__) ; 
 struct sk_buff* fq_dequeue_head (struct Qdisc*,struct fq_flow*) ; 
 int /*<<< orphan*/  fq_flow_add_tail (struct fq_flow_head*,struct fq_flow*) ; 
 int /*<<< orphan*/  fq_flow_set_detached (struct fq_flow*) ; 
 int /*<<< orphan*/  fq_flow_set_throttled (struct fq_sched_data*,struct fq_flow*) ; 
 scalar_t__ ktime_get_ns () ; 
 scalar_t__ likely (unsigned int) ; 
 unsigned int max (unsigned int,scalar_t__) ; 
 unsigned int min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  prefetch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qdisc_bstats_update (struct Qdisc*,struct sk_buff*) ; 
 unsigned int qdisc_pkt_len (struct sk_buff*) ; 
 struct fq_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_watchdog_schedule_ns (int /*<<< orphan*/ *,unsigned long long) ; 
 scalar_t__ skb_is_tcp_pure_ack (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *fq_dequeue(struct Qdisc *sch)
{
	struct fq_sched_data *q = qdisc_priv(sch);
	u64 now = ktime_get_ns();
	struct fq_flow_head *head;
	struct sk_buff *skb;
	struct fq_flow *f;
	u32 rate, plen;

	skb = fq_dequeue_head(sch, &q->internal);
	if (skb)
		goto out;
	fq_check_throttled(q, now);
begin:
	head = &q->new_flows;
	if (!head->first) {
		head = &q->old_flows;
		if (!head->first) {
			if (q->time_next_delayed_flow != ~0ULL)
				qdisc_watchdog_schedule_ns(&q->watchdog,
							   q->time_next_delayed_flow);
			return NULL;
		}
	}
	f = head->first;

	if (f->credit <= 0) {
		f->credit += q->quantum;
		head->first = f->next;
		fq_flow_add_tail(&q->old_flows, f);
		goto begin;
	}

	skb = f->head;
	if (unlikely(skb && now < f->time_next_packet &&
		     !skb_is_tcp_pure_ack(skb))) {
		head->first = f->next;
		fq_flow_set_throttled(q, f);
		goto begin;
	}

	skb = fq_dequeue_head(sch, f);
	if (!skb) {
		head->first = f->next;
		/* force a pass through old_flows to prevent starvation */
		if ((head == &q->new_flows) && q->old_flows.first) {
			fq_flow_add_tail(&q->old_flows, f);
		} else {
			fq_flow_set_detached(f);
			q->inactive_flows++;
		}
		goto begin;
	}
	prefetch(&skb->end);
	f->credit -= qdisc_pkt_len(skb);

	if (!q->rate_enable)
		goto out;

	/* Do not pace locally generated ack packets */
	if (skb_is_tcp_pure_ack(skb))
		goto out;

	rate = q->flow_max_rate;
	if (skb->sk)
		rate = min(skb->sk->sk_pacing_rate, rate);

	if (rate <= q->low_rate_threshold) {
		f->credit = 0;
		plen = qdisc_pkt_len(skb);
	} else {
		plen = max(qdisc_pkt_len(skb), q->quantum);
		if (f->credit > 0)
			goto out;
	}
	if (rate != ~0U) {
		u64 len = (u64)plen * NSEC_PER_SEC;

		if (likely(rate))
			do_div(len, rate);
		/* Since socket rate can change later,
		 * clamp the delay to 1 second.
		 * Really, providers of too big packets should be fixed !
		 */
		if (unlikely(len > NSEC_PER_SEC)) {
			len = NSEC_PER_SEC;
			q->stat_pkts_too_long++;
		}
		/* Account for schedule/timers drifts.
		 * f->time_next_packet was set when prior packet was sent,
		 * and current time (@now) can be too late by tens of us.
		 */
		if (f->time_next_packet)
			len -= min(len/2, now - f->time_next_packet);
		f->time_next_packet = now + len;
	}
out:
	qdisc_bstats_update(sch, skb);
	return skb;
}