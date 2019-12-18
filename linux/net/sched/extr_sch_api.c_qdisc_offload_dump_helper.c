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
struct net_device {TYPE_1__* netdev_ops; } ;
struct Qdisc {int /*<<< orphan*/  flags; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;
struct TYPE_2__ {int (* ndo_setup_tc ) (struct net_device*,int,void*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  TCQ_F_OFFLOADED ; 
 struct net_device* qdisc_dev (struct Qdisc*) ; 
 int stub1 (struct net_device*,int,void*) ; 
 int /*<<< orphan*/  tc_can_offload (struct net_device*) ; 

int qdisc_offload_dump_helper(struct Qdisc *sch, enum tc_setup_type type,
			      void *type_data)
{
	struct net_device *dev = qdisc_dev(sch);
	int err;

	sch->flags &= ~TCQ_F_OFFLOADED;
	if (!tc_can_offload(dev) || !dev->netdev_ops->ndo_setup_tc)
		return 0;

	err = dev->netdev_ops->ndo_setup_tc(dev, type, type_data);
	if (err == -EOPNOTSUPP)
		return 0;

	if (!err)
		sch->flags |= TCQ_F_OFFLOADED;

	return err;
}