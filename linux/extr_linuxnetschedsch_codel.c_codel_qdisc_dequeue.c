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
struct sk_buff {int dummy; } ;
struct TYPE_6__ {scalar_t__ drop_len; scalar_t__ drop_count; } ;
struct codel_sched_data {TYPE_3__ stats; int /*<<< orphan*/  vars; int /*<<< orphan*/  params; } ;
struct TYPE_5__ {scalar_t__ qlen; } ;
struct TYPE_4__ {int /*<<< orphan*/  backlog; } ;
struct Qdisc {TYPE_2__ q; TYPE_1__ qstats; } ;

/* Variables and functions */
 struct sk_buff* codel_dequeue (struct Qdisc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  codel_get_enqueue_time ; 
 int /*<<< orphan*/  dequeue_func ; 
 int /*<<< orphan*/  drop_func ; 
 int /*<<< orphan*/  qdisc_bstats_update (struct Qdisc*,struct sk_buff*) ; 
 int /*<<< orphan*/  qdisc_pkt_len ; 
 struct codel_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_tree_reduce_backlog (struct Qdisc*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct sk_buff *codel_qdisc_dequeue(struct Qdisc *sch)
{
	struct codel_sched_data *q = qdisc_priv(sch);
	struct sk_buff *skb;

	skb = codel_dequeue(sch, &sch->qstats.backlog, &q->params, &q->vars,
			    &q->stats, qdisc_pkt_len, codel_get_enqueue_time,
			    drop_func, dequeue_func);

	/* We cant call qdisc_tree_reduce_backlog() if our qlen is 0,
	 * or HTB crashes. Defer it for next round.
	 */
	if (q->stats.drop_count && sch->q.qlen) {
		qdisc_tree_reduce_backlog(sch, q->stats.drop_count, q->stats.drop_len);
		q->stats.drop_count = 0;
		q->stats.drop_len = 0;
	}
	if (skb)
		qdisc_bstats_update(sch, skb);
	return skb;
}