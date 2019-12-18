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
struct TYPE_2__ {scalar_t__ qlen; } ;
struct teql_sched_data {TYPE_1__ q; } ;
struct sk_buff {int dummy; } ;
struct net_device {scalar_t__ tx_queue_len; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int NET_XMIT_SUCCESS ; 
 int /*<<< orphan*/  __skb_queue_tail (TYPE_1__*,struct sk_buff*) ; 
 struct net_device* qdisc_dev (struct Qdisc*) ; 
 int qdisc_drop (struct sk_buff*,struct Qdisc*,struct sk_buff**) ; 
 struct teql_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static int
teql_enqueue(struct sk_buff *skb, struct Qdisc *sch, struct sk_buff **to_free)
{
	struct net_device *dev = qdisc_dev(sch);
	struct teql_sched_data *q = qdisc_priv(sch);

	if (q->q.qlen < dev->tx_queue_len) {
		__skb_queue_tail(&q->q, skb);
		return NET_XMIT_SUCCESS;
	}

	return qdisc_drop(skb, sch, to_free);
}