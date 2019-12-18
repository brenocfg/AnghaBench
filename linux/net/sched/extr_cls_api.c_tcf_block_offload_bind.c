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
struct tcf_block_ext_info {int dummy; } ;
struct tcf_block {int /*<<< orphan*/  cb_lock; int /*<<< orphan*/  nooffloaddevcnt; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {TYPE_2__* netdev_ops; } ;
struct Qdisc {TYPE_1__* dev_queue; } ;
struct TYPE_4__ {int /*<<< orphan*/  ndo_setup_tc; } ;
struct TYPE_3__ {struct net_device* dev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  FLOW_BLOCK_BIND ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tc_can_offload (struct net_device*) ; 
 int /*<<< orphan*/  tc_indr_block_call (struct tcf_block*,struct net_device*,struct tcf_block_ext_info*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int tcf_block_offload_cmd (struct tcf_block*,struct net_device*,struct tcf_block_ext_info*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 scalar_t__ tcf_block_offload_in_use (struct tcf_block*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tcf_block_offload_bind(struct tcf_block *block, struct Qdisc *q,
				  struct tcf_block_ext_info *ei,
				  struct netlink_ext_ack *extack)
{
	struct net_device *dev = q->dev_queue->dev;
	int err;

	down_write(&block->cb_lock);
	if (!dev->netdev_ops->ndo_setup_tc)
		goto no_offload_dev_inc;

	/* If tc offload feature is disabled and the block we try to bind
	 * to already has some offloaded filters, forbid to bind.
	 */
	if (!tc_can_offload(dev) && tcf_block_offload_in_use(block)) {
		NL_SET_ERR_MSG(extack, "Bind to offloaded block failed as dev has offload disabled");
		err = -EOPNOTSUPP;
		goto err_unlock;
	}

	err = tcf_block_offload_cmd(block, dev, ei, FLOW_BLOCK_BIND, extack);
	if (err == -EOPNOTSUPP)
		goto no_offload_dev_inc;
	if (err)
		goto err_unlock;

	tc_indr_block_call(block, dev, ei, FLOW_BLOCK_BIND, extack);
	up_write(&block->cb_lock);
	return 0;

no_offload_dev_inc:
	if (tcf_block_offload_in_use(block)) {
		err = -EOPNOTSUPP;
		goto err_unlock;
	}
	err = 0;
	block->nooffloaddevcnt++;
	tc_indr_block_call(block, dev, ei, FLOW_BLOCK_BIND, extack);
err_unlock:
	up_write(&block->cb_lock);
	return err;
}