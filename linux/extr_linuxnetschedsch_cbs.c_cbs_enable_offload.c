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
struct tc_cbs_qopt_offload {int enable; int /*<<< orphan*/  sendslope; int /*<<< orphan*/  idleslope; int /*<<< orphan*/  locredit; int /*<<< orphan*/  hicredit; int /*<<< orphan*/  queue; } ;
struct tc_cbs_qopt {int /*<<< orphan*/  sendslope; int /*<<< orphan*/  idleslope; int /*<<< orphan*/  locredit; int /*<<< orphan*/  hicredit; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device_ops {int (* ndo_setup_tc ) (struct net_device*,int /*<<< orphan*/ ,struct tc_cbs_qopt_offload*) ;} ;
struct net_device {struct net_device_ops* netdev_ops; } ;
struct cbs_sched_data {int /*<<< orphan*/  dequeue; int /*<<< orphan*/  enqueue; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  TC_SETUP_QDISC_CBS ; 
 int /*<<< orphan*/  cbs_dequeue_offload ; 
 int /*<<< orphan*/  cbs_enqueue_offload ; 
 int stub1 (struct net_device*,int /*<<< orphan*/ ,struct tc_cbs_qopt_offload*) ; 

__attribute__((used)) static int cbs_enable_offload(struct net_device *dev, struct cbs_sched_data *q,
			      const struct tc_cbs_qopt *opt,
			      struct netlink_ext_ack *extack)
{
	const struct net_device_ops *ops = dev->netdev_ops;
	struct tc_cbs_qopt_offload cbs = { };
	int err;

	if (!ops->ndo_setup_tc) {
		NL_SET_ERR_MSG(extack, "Specified device does not support cbs offload");
		return -EOPNOTSUPP;
	}

	cbs.queue = q->queue;

	cbs.enable = 1;
	cbs.hicredit = opt->hicredit;
	cbs.locredit = opt->locredit;
	cbs.idleslope = opt->idleslope;
	cbs.sendslope = opt->sendslope;

	err = ops->ndo_setup_tc(dev, TC_SETUP_QDISC_CBS, &cbs);
	if (err < 0) {
		NL_SET_ERR_MSG(extack, "Specified device failed to setup cbs hardware offload");
		return err;
	}

	q->enqueue = cbs_enqueue_offload;
	q->dequeue = cbs_dequeue_offload;

	return 0;
}