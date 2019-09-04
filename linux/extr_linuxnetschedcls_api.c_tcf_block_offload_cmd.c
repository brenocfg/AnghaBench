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
struct tcf_block_ext_info {int /*<<< orphan*/  binder_type; } ;
struct tcf_block {int dummy; } ;
struct tc_block_offload {int command; struct netlink_ext_ack* extack; struct tcf_block* block; int /*<<< orphan*/  binder_type; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {TYPE_1__* netdev_ops; } ;
typedef  enum tc_block_command { ____Placeholder_tc_block_command } tc_block_command ;
struct TYPE_2__ {int (* ndo_setup_tc ) (struct net_device*,int /*<<< orphan*/ ,struct tc_block_offload*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TC_SETUP_BLOCK ; 
 int stub1 (struct net_device*,int /*<<< orphan*/ ,struct tc_block_offload*) ; 

__attribute__((used)) static int tcf_block_offload_cmd(struct tcf_block *block,
				 struct net_device *dev,
				 struct tcf_block_ext_info *ei,
				 enum tc_block_command command,
				 struct netlink_ext_ack *extack)
{
	struct tc_block_offload bo = {};

	bo.command = command;
	bo.binder_type = ei->binder_type;
	bo.block = block;
	bo.extack = extack;
	return dev->netdev_ops->ndo_setup_tc(dev, TC_SETUP_BLOCK, &bo);
}