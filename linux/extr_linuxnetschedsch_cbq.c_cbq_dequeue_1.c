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
struct sk_buff {int dummy; } ;
struct cbq_sched_data {int activemask; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 struct sk_buff* cbq_dequeue_prio (struct Qdisc*,int) ; 
 int ffz (unsigned int) ; 
 struct cbq_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static inline struct sk_buff *
cbq_dequeue_1(struct Qdisc *sch)
{
	struct cbq_sched_data *q = qdisc_priv(sch);
	struct sk_buff *skb;
	unsigned int activemask;

	activemask = q->activemask & 0xFF;
	while (activemask) {
		int prio = ffz(~activemask);
		activemask &= ~(1<<prio);
		skb = cbq_dequeue_prio(sch, prio);
		if (skb)
			return skb;
	}
	return NULL;
}