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
struct choke_sched_data {unsigned int head; unsigned int tail; struct sk_buff** tab; } ;
struct TYPE_2__ {int /*<<< orphan*/  qlen; } ;
struct Qdisc {TYPE_1__ q; } ;

/* Variables and functions */
 int /*<<< orphan*/  choke_zap_head_holes (struct choke_sched_data*) ; 
 int /*<<< orphan*/  choke_zap_tail_holes (struct choke_sched_data*) ; 
 int /*<<< orphan*/  qdisc_drop (struct sk_buff*,struct Qdisc*,struct sk_buff**) ; 
 int /*<<< orphan*/  qdisc_pkt_len (struct sk_buff*) ; 
 struct choke_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_qstats_backlog_dec (struct Qdisc*,struct sk_buff*) ; 
 int /*<<< orphan*/  qdisc_tree_reduce_backlog (struct Qdisc*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void choke_drop_by_idx(struct Qdisc *sch, unsigned int idx,
			      struct sk_buff **to_free)
{
	struct choke_sched_data *q = qdisc_priv(sch);
	struct sk_buff *skb = q->tab[idx];

	q->tab[idx] = NULL;

	if (idx == q->head)
		choke_zap_head_holes(q);
	if (idx == q->tail)
		choke_zap_tail_holes(q);

	qdisc_qstats_backlog_dec(sch, skb);
	qdisc_tree_reduce_backlog(sch, 1, qdisc_pkt_len(skb));
	qdisc_drop(skb, sch, to_free);
	--sch->q.qlen;
}