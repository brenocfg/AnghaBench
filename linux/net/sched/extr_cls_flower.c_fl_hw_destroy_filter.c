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
struct tcf_proto {TYPE_1__* chain; } ;
struct tcf_block {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct flow_cls_offload {unsigned long cookie; int /*<<< orphan*/  command; int /*<<< orphan*/  common; } ;
struct cls_fl_filter {int /*<<< orphan*/  in_hw_count; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {struct tcf_block* block; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLOW_CLS_DESTROY ; 
 int /*<<< orphan*/  TC_SETUP_CLSFLOWER ; 
 int /*<<< orphan*/  tc_cls_common_offload_init (int /*<<< orphan*/ *,struct tcf_proto*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  tc_setup_cb_destroy (struct tcf_block*,struct tcf_proto*,int /*<<< orphan*/ ,struct flow_cls_offload*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void fl_hw_destroy_filter(struct tcf_proto *tp, struct cls_fl_filter *f,
				 bool rtnl_held, struct netlink_ext_ack *extack)
{
	struct tcf_block *block = tp->chain->block;
	struct flow_cls_offload cls_flower = {};

	tc_cls_common_offload_init(&cls_flower.common, tp, f->flags, extack);
	cls_flower.command = FLOW_CLS_DESTROY;
	cls_flower.cookie = (unsigned long) f;

	tc_setup_cb_destroy(block, tp, TC_SETUP_CLSFLOWER, &cls_flower, false,
			    &f->flags, &f->in_hw_count, rtnl_held);

}