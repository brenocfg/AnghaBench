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
struct tc_taprio_qopt_offload {int enable; } ;
struct tc_mqprio_qopt {int dummy; } ;
struct taprio_sched {int dummy; } ;
struct sched_gate_list {int /*<<< orphan*/  num_entries; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device_ops {int (* ndo_setup_tc ) (struct net_device*,int /*<<< orphan*/ ,struct tc_taprio_qopt_offload*) ;} ;
struct net_device {struct net_device_ops* netdev_ops; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  TC_SETUP_QDISC_TAPRIO ; 
 int stub1 (struct net_device*,int /*<<< orphan*/ ,struct tc_taprio_qopt_offload*) ; 
 struct tc_taprio_qopt_offload* taprio_offload_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taprio_offload_free (struct tc_taprio_qopt_offload*) ; 
 int /*<<< orphan*/  taprio_sched_to_offload (struct taprio_sched*,struct sched_gate_list*,struct tc_mqprio_qopt*,struct tc_taprio_qopt_offload*) ; 

__attribute__((used)) static int taprio_enable_offload(struct net_device *dev,
				 struct tc_mqprio_qopt *mqprio,
				 struct taprio_sched *q,
				 struct sched_gate_list *sched,
				 struct netlink_ext_ack *extack)
{
	const struct net_device_ops *ops = dev->netdev_ops;
	struct tc_taprio_qopt_offload *offload;
	int err = 0;

	if (!ops->ndo_setup_tc) {
		NL_SET_ERR_MSG(extack,
			       "Device does not support taprio offload");
		return -EOPNOTSUPP;
	}

	offload = taprio_offload_alloc(sched->num_entries);
	if (!offload) {
		NL_SET_ERR_MSG(extack,
			       "Not enough memory for enabling offload mode");
		return -ENOMEM;
	}
	offload->enable = 1;
	taprio_sched_to_offload(q, sched, mqprio, offload);

	err = ops->ndo_setup_tc(dev, TC_SETUP_QDISC_TAPRIO, offload);
	if (err < 0) {
		NL_SET_ERR_MSG(extack,
			       "Device failed to setup taprio offload");
		goto done;
	}

done:
	taprio_offload_free(offload);

	return err;
}