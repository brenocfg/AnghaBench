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
struct sk_buff {scalar_t__ len; } ;
struct plug_sched_data {scalar_t__ limit; int /*<<< orphan*/  pkts_current_epoch; int /*<<< orphan*/  unplug_indefinite; } ;
struct TYPE_2__ {scalar_t__ backlog; } ;
struct Qdisc {TYPE_1__ qstats; } ;

/* Variables and functions */
 scalar_t__ likely (int) ; 
 int qdisc_drop (struct sk_buff*,struct Qdisc*,struct sk_buff**) ; 
 int qdisc_enqueue_tail (struct sk_buff*,struct Qdisc*) ; 
 struct plug_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static int plug_enqueue(struct sk_buff *skb, struct Qdisc *sch,
			struct sk_buff **to_free)
{
	struct plug_sched_data *q = qdisc_priv(sch);

	if (likely(sch->qstats.backlog + skb->len <= q->limit)) {
		if (!q->unplug_indefinite)
			q->pkts_current_epoch++;
		return qdisc_enqueue_tail(skb, sch);
	}

	return qdisc_drop(skb, sch, to_free);
}