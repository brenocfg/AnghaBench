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
struct tcf_block {int dummy; } ;
struct qfq_sched {struct tcf_block* block; } ;
struct netlink_ext_ack {int dummy; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 struct qfq_sched* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static struct tcf_block *qfq_tcf_block(struct Qdisc *sch, unsigned long cl,
				       struct netlink_ext_ack *extack)
{
	struct qfq_sched *q = qdisc_priv(sch);

	if (cl)
		return NULL;

	return q->block;
}