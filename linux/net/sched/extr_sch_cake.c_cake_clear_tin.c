#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct cake_sched_data {scalar_t__ cur_flow; int /*<<< orphan*/  cur_tin; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 scalar_t__ CAKE_QUEUES ; 
 struct sk_buff* cake_dequeue_one (struct Qdisc*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct cake_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static void cake_clear_tin(struct Qdisc *sch, u16 tin)
{
	struct cake_sched_data *q = qdisc_priv(sch);
	struct sk_buff *skb;

	q->cur_tin = tin;
	for (q->cur_flow = 0; q->cur_flow < CAKE_QUEUES; q->cur_flow++)
		while (!!(skb = cake_dequeue_one(sch)))
			kfree_skb(skb);
}