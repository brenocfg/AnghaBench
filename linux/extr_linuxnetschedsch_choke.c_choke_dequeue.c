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
struct choke_sched_data {size_t head; size_t tail; struct sk_buff** tab; int /*<<< orphan*/  vars; } ;
struct TYPE_2__ {int /*<<< orphan*/  qlen; } ;
struct Qdisc {TYPE_1__ q; } ;

/* Variables and functions */
 int /*<<< orphan*/  choke_zap_head_holes (struct choke_sched_data*) ; 
 int /*<<< orphan*/  qdisc_bstats_update (struct Qdisc*,struct sk_buff*) ; 
 struct choke_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_qstats_backlog_dec (struct Qdisc*,struct sk_buff*) ; 
 int /*<<< orphan*/  red_is_idling (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  red_start_of_idle_period (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct sk_buff *choke_dequeue(struct Qdisc *sch)
{
	struct choke_sched_data *q = qdisc_priv(sch);
	struct sk_buff *skb;

	if (q->head == q->tail) {
		if (!red_is_idling(&q->vars))
			red_start_of_idle_period(&q->vars);
		return NULL;
	}

	skb = q->tab[q->head];
	q->tab[q->head] = NULL;
	choke_zap_head_holes(q);
	--sch->q.qlen;
	qdisc_qstats_backlog_dec(sch, skb);
	qdisc_bstats_update(sch, skb);

	return skb;
}