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
struct sk_buff {int dummy; } ;
struct red_sched_data {int /*<<< orphan*/  vars; struct Qdisc* qdisc; } ;
struct TYPE_2__ {int /*<<< orphan*/  qlen; } ;
struct Qdisc {TYPE_1__ q; struct sk_buff* (* dequeue ) (struct Qdisc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  qdisc_bstats_update (struct Qdisc*,struct sk_buff*) ; 
 struct red_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_qstats_backlog_dec (struct Qdisc*,struct sk_buff*) ; 
 int /*<<< orphan*/  red_is_idling (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  red_start_of_idle_period (int /*<<< orphan*/ *) ; 
 struct sk_buff* stub1 (struct Qdisc*) ; 

__attribute__((used)) static struct sk_buff *red_dequeue(struct Qdisc *sch)
{
	struct sk_buff *skb;
	struct red_sched_data *q = qdisc_priv(sch);
	struct Qdisc *child = q->qdisc;

	skb = child->dequeue(child);
	if (skb) {
		qdisc_bstats_update(sch, skb);
		qdisc_qstats_backlog_dec(sch, skb);
		sch->q.qlen--;
	} else {
		if (!red_is_idling(&q->vars))
			red_start_of_idle_period(&q->vars);
	}
	return skb;
}