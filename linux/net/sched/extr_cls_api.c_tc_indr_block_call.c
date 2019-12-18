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
struct tcf_block_ext_info {int /*<<< orphan*/  binder_type; } ;
struct tcf_block {int /*<<< orphan*/  flow_block; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct flow_block_offload {int command; int /*<<< orphan*/  cb_list; struct netlink_ext_ack* extack; int /*<<< orphan*/  block_shared; int /*<<< orphan*/ * block; int /*<<< orphan*/  net; int /*<<< orphan*/  binder_type; } ;
typedef  enum flow_block_command { ____Placeholder_flow_block_command } flow_block_command ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  flow_indr_block_call (struct net_device*,struct flow_block_offload*,int) ; 
 int /*<<< orphan*/  tcf_block_setup (struct tcf_block*,struct flow_block_offload*) ; 
 int /*<<< orphan*/  tcf_block_shared (struct tcf_block*) ; 

__attribute__((used)) static void tc_indr_block_call(struct tcf_block *block,
			       struct net_device *dev,
			       struct tcf_block_ext_info *ei,
			       enum flow_block_command command,
			       struct netlink_ext_ack *extack)
{
	struct flow_block_offload bo = {
		.command	= command,
		.binder_type	= ei->binder_type,
		.net		= dev_net(dev),
		.block		= &block->flow_block,
		.block_shared	= tcf_block_shared(block),
		.extack		= extack,
	};
	INIT_LIST_HEAD(&bo.cb_list);

	flow_indr_block_call(dev, &bo, command);
	tcf_block_setup(block, &bo);
}