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
struct taprio_sched {struct Qdisc** qdiscs; } ;
struct sk_buff {int dummy; } ;
struct net_device {int num_tx_queues; } ;
struct Qdisc {TYPE_1__* ops; } ;
struct TYPE_2__ {struct sk_buff* (* peek ) (struct Qdisc*) ;} ;

/* Variables and functions */
 struct net_device* qdisc_dev (struct Qdisc*) ; 
 struct taprio_sched* qdisc_priv (struct Qdisc*) ; 
 struct sk_buff* stub1 (struct Qdisc*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *taprio_peek_offload(struct Qdisc *sch)
{
	struct taprio_sched *q = qdisc_priv(sch);
	struct net_device *dev = qdisc_dev(sch);
	struct sk_buff *skb;
	int i;

	for (i = 0; i < dev->num_tx_queues; i++) {
		struct Qdisc *child = q->qdiscs[i];

		if (unlikely(!child))
			continue;

		skb = child->ops->peek(child);
		if (!skb)
			continue;

		return skb;
	}

	return NULL;
}