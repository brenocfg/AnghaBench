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
struct netlink_ext_ack {int dummy; } ;
struct net_device {TYPE_1__* netdev_ops; } ;
struct Qdisc {int flags; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;
struct TYPE_2__ {int (* ndo_setup_tc ) (struct net_device*,int,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int TCQ_F_OFFLOADED ; 
 struct Qdisc noop_qdisc ; 
 int stub1 (struct net_device*,int,void*) ; 
 int /*<<< orphan*/  tc_can_offload (struct net_device*) ; 

void qdisc_offload_graft_helper(struct net_device *dev, struct Qdisc *sch,
				struct Qdisc *new, struct Qdisc *old,
				enum tc_setup_type type, void *type_data,
				struct netlink_ext_ack *extack)
{
	bool any_qdisc_is_offloaded;
	int err;

	if (!tc_can_offload(dev) || !dev->netdev_ops->ndo_setup_tc)
		return;

	err = dev->netdev_ops->ndo_setup_tc(dev, type, type_data);

	/* Don't report error if the graft is part of destroy operation. */
	if (!err || !new || new == &noop_qdisc)
		return;

	/* Don't report error if the parent, the old child and the new
	 * one are not offloaded.
	 */
	any_qdisc_is_offloaded = new->flags & TCQ_F_OFFLOADED;
	any_qdisc_is_offloaded |= sch && sch->flags & TCQ_F_OFFLOADED;
	any_qdisc_is_offloaded |= old && old->flags & TCQ_F_OFFLOADED;

	if (any_qdisc_is_offloaded)
		NL_SET_ERR_MSG(extack, "Offloading graft operation failed.");
}