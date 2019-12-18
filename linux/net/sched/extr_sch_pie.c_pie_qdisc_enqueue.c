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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct TYPE_6__ {int prob; scalar_t__ accu_prob_overflows; scalar_t__ accu_prob; } ;
struct TYPE_5__ {scalar_t__ maxq; int /*<<< orphan*/  dropped; int /*<<< orphan*/  packets_in; int /*<<< orphan*/  ecn_mark; int /*<<< orphan*/  overlimit; } ;
struct TYPE_4__ {scalar_t__ ecn; } ;
struct pie_sched_data {TYPE_3__ vars; TYPE_2__ stats; TYPE_1__ params; } ;
struct Qdisc {scalar_t__ limit; } ;

/* Variables and functions */
 scalar_t__ INET_ECN_set_ce (struct sk_buff*) ; 
 int MAX_PROB ; 
 int /*<<< orphan*/  drop_early (struct Qdisc*,int /*<<< orphan*/ ) ; 
 int qdisc_drop (struct sk_buff*,struct Qdisc*,struct sk_buff**) ; 
 int qdisc_enqueue_tail (struct sk_buff*,struct Qdisc*) ; 
 struct pie_sched_data* qdisc_priv (struct Qdisc*) ; 
 scalar_t__ qdisc_qlen (struct Qdisc*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int pie_qdisc_enqueue(struct sk_buff *skb, struct Qdisc *sch,
			     struct sk_buff **to_free)
{
	struct pie_sched_data *q = qdisc_priv(sch);
	bool enqueue = false;

	if (unlikely(qdisc_qlen(sch) >= sch->limit)) {
		q->stats.overlimit++;
		goto out;
	}

	if (!drop_early(sch, skb->len)) {
		enqueue = true;
	} else if (q->params.ecn && (q->vars.prob <= MAX_PROB / 10) &&
		   INET_ECN_set_ce(skb)) {
		/* If packet is ecn capable, mark it if drop probability
		 * is lower than 10%, else drop it.
		 */
		q->stats.ecn_mark++;
		enqueue = true;
	}

	/* we can enqueue the packet */
	if (enqueue) {
		q->stats.packets_in++;
		if (qdisc_qlen(sch) > q->stats.maxq)
			q->stats.maxq = qdisc_qlen(sch);

		return qdisc_enqueue_tail(skb, sch);
	}

out:
	q->stats.dropped++;
	q->vars.accu_prob = 0;
	q->vars.accu_prob_overflows = 0;
	return qdisc_drop(skb, sch, to_free);
}