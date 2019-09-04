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
struct tcmsg {int /*<<< orphan*/  tcm_info; int /*<<< orphan*/  tcm_handle; } ;
struct sk_buff {int dummy; } ;
struct prio_sched_data {TYPE_1__** queues; } ;
struct Qdisc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  TC_H_MIN (unsigned long) ; 
 struct prio_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static int prio_dump_class(struct Qdisc *sch, unsigned long cl, struct sk_buff *skb,
			   struct tcmsg *tcm)
{
	struct prio_sched_data *q = qdisc_priv(sch);

	tcm->tcm_handle |= TC_H_MIN(cl);
	tcm->tcm_info = q->queues[cl-1]->handle;
	return 0;
}