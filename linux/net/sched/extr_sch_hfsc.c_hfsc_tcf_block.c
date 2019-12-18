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
struct netlink_ext_ack {int dummy; } ;
struct hfsc_class {struct tcf_block* block; } ;
struct hfsc_sched {struct hfsc_class root; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 struct hfsc_sched* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static struct tcf_block *hfsc_tcf_block(struct Qdisc *sch, unsigned long arg,
					struct netlink_ext_ack *extack)
{
	struct hfsc_sched *q = qdisc_priv(sch);
	struct hfsc_class *cl = (struct hfsc_class *)arg;

	if (cl == NULL)
		cl = &q->root;

	return cl->block;
}