#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long band; int /*<<< orphan*/  child_handle; } ;
struct tc_prio_qopt_offload {int /*<<< orphan*/  command; TYPE_1__ graft_params; int /*<<< orphan*/  parent; int /*<<< orphan*/  handle; } ;
struct prio_sched_data {int /*<<< orphan*/ * queues; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {TYPE_2__* netdev_ops; } ;
struct Qdisc {int flags; int /*<<< orphan*/  handle; int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {int (* ndo_setup_tc ) (struct net_device*,int /*<<< orphan*/ ,struct tc_prio_qopt_offload*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int TCQ_F_OFFLOADED ; 
 int /*<<< orphan*/  TC_PRIO_GRAFT ; 
 int /*<<< orphan*/  TC_SETUP_QDISC_PRIO ; 
 struct Qdisc noop_qdisc ; 
 struct net_device* qdisc_dev (struct Qdisc*) ; 
 struct prio_sched_data* qdisc_priv (struct Qdisc*) ; 
 struct Qdisc* qdisc_replace (struct Qdisc*,struct Qdisc*,int /*<<< orphan*/ *) ; 
 int stub1 (struct net_device*,int /*<<< orphan*/ ,struct tc_prio_qopt_offload*) ; 
 int /*<<< orphan*/  tc_can_offload (struct net_device*) ; 

__attribute__((used)) static int prio_graft(struct Qdisc *sch, unsigned long arg, struct Qdisc *new,
		      struct Qdisc **old, struct netlink_ext_ack *extack)
{
	struct prio_sched_data *q = qdisc_priv(sch);
	struct tc_prio_qopt_offload graft_offload;
	struct net_device *dev = qdisc_dev(sch);
	unsigned long band = arg - 1;
	bool any_qdisc_is_offloaded;
	int err;

	if (new == NULL)
		new = &noop_qdisc;

	*old = qdisc_replace(sch, new, &q->queues[band]);

	if (!tc_can_offload(dev))
		return 0;

	graft_offload.handle = sch->handle;
	graft_offload.parent = sch->parent;
	graft_offload.graft_params.band = band;
	graft_offload.graft_params.child_handle = new->handle;
	graft_offload.command = TC_PRIO_GRAFT;

	err = dev->netdev_ops->ndo_setup_tc(dev, TC_SETUP_QDISC_PRIO,
					    &graft_offload);

	/* Don't report error if the graft is part of destroy operation. */
	if (err && new != &noop_qdisc) {
		/* Don't report error if the parent, the old child and the new
		 * one are not offloaded.
		 */
		any_qdisc_is_offloaded = sch->flags & TCQ_F_OFFLOADED;
		any_qdisc_is_offloaded |= new->flags & TCQ_F_OFFLOADED;
		if (*old)
			any_qdisc_is_offloaded |= (*old)->flags &
						   TCQ_F_OFFLOADED;

		if (any_qdisc_is_offloaded)
			NL_SET_ERR_MSG(extack, "Offloading graft operation failed.");
	}

	return 0;
}