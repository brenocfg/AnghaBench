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
struct cbs_sched_data {struct sk_buff* (* dequeue ) (struct Qdisc*) ;} ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 struct cbs_sched_data* qdisc_priv (struct Qdisc*) ; 
 struct sk_buff* stub1 (struct Qdisc*) ; 

__attribute__((used)) static struct sk_buff *cbs_dequeue(struct Qdisc *sch)
{
	struct cbs_sched_data *q = qdisc_priv(sch);

	return q->dequeue(sch);
}