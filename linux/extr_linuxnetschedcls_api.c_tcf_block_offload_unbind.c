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
struct tcf_block {int /*<<< orphan*/  nooffloaddevcnt; } ;
struct net_device {TYPE_2__* netdev_ops; } ;
struct Qdisc {TYPE_1__* dev_queue; } ;
struct TYPE_4__ {int /*<<< orphan*/  ndo_setup_tc; } ;
struct TYPE_3__ {struct net_device* dev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  TC_BLOCK_UNBIND ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int tcf_block_offload_cmd (struct tcf_block*,struct net_device*,struct tcf_block_ext_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tcf_block_offload_unbind(struct tcf_block *block, struct Qdisc *q,
				     struct tcf_block_ext_info *ei)
{
	struct net_device *dev = q->dev_queue->dev;
	int err;

	if (!dev->netdev_ops->ndo_setup_tc)
		goto no_offload_dev_dec;
	err = tcf_block_offload_cmd(block, dev, ei, TC_BLOCK_UNBIND, NULL);
	if (err == -EOPNOTSUPP)
		goto no_offload_dev_dec;
	return;

no_offload_dev_dec:
	WARN_ON(block->nooffloaddevcnt-- == 0);
}