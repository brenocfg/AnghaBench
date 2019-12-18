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
struct TYPE_2__ {unsigned long band; int /*<<< orphan*/  child_handle; } ;
struct tc_prio_qopt_offload {int /*<<< orphan*/  command; TYPE_1__ graft_params; int /*<<< orphan*/  parent; int /*<<< orphan*/  handle; } ;
struct prio_sched_data {int /*<<< orphan*/ * queues; } ;
struct netlink_ext_ack {int dummy; } ;
struct Qdisc {int /*<<< orphan*/  handle; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  TC_PRIO_GRAFT ; 
 int /*<<< orphan*/  TC_SETUP_QDISC_PRIO ; 
 struct Qdisc noop_qdisc ; 
 int /*<<< orphan*/  qdisc_dev (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_offload_graft_helper (int /*<<< orphan*/ ,struct Qdisc*,struct Qdisc*,struct Qdisc*,int /*<<< orphan*/ ,struct tc_prio_qopt_offload*,struct netlink_ext_ack*) ; 
 struct prio_sched_data* qdisc_priv (struct Qdisc*) ; 
 struct Qdisc* qdisc_replace (struct Qdisc*,struct Qdisc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int prio_graft(struct Qdisc *sch, unsigned long arg, struct Qdisc *new,
		      struct Qdisc **old, struct netlink_ext_ack *extack)
{
	struct prio_sched_data *q = qdisc_priv(sch);
	struct tc_prio_qopt_offload graft_offload;
	unsigned long band = arg - 1;

	if (new == NULL)
		new = &noop_qdisc;

	*old = qdisc_replace(sch, new, &q->queues[band]);

	graft_offload.handle = sch->handle;
	graft_offload.parent = sch->parent;
	graft_offload.graft_params.band = band;
	graft_offload.graft_params.child_handle = new->handle;
	graft_offload.command = TC_PRIO_GRAFT;

	qdisc_offload_graft_helper(qdisc_dev(sch), sch, new, *old,
				   TC_SETUP_QDISC_PRIO, &graft_offload,
				   extack);
	return 0;
}