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
struct netem_sched_data {TYPE_1__* qdisc; } ;
struct Qdisc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  TC_H_MIN (int) ; 
 struct netem_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static int netem_dump_class(struct Qdisc *sch, unsigned long cl,
			  struct sk_buff *skb, struct tcmsg *tcm)
{
	struct netem_sched_data *q = qdisc_priv(sch);

	if (cl != 1 || !q->qdisc) 	/* only one class */
		return -ENOENT;

	tcm->tcm_handle |= TC_H_MIN(1);
	tcm->tcm_info = q->qdisc->handle;

	return 0;
}