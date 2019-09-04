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
struct tc_cls_flower_offload {unsigned long cookie; int /*<<< orphan*/  command; int /*<<< orphan*/  common; } ;
struct netlink_ext_ack {int dummy; } ;
struct cls_fl_filter {int /*<<< orphan*/  flags; int /*<<< orphan*/  exts; } ;
struct TYPE_2__ {struct tcf_block* block; } ;

/* Variables and functions */
 int /*<<< orphan*/  TC_CLSFLOWER_DESTROY ; 
 int /*<<< orphan*/  TC_SETUP_CLSFLOWER ; 
 int /*<<< orphan*/  tc_cls_common_offload_init (int /*<<< orphan*/ *,struct tcf_proto*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  tc_setup_cb_call (struct tcf_block*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct tc_cls_flower_offload*,int) ; 
 int /*<<< orphan*/  tcf_block_offload_dec (struct tcf_block*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fl_hw_destroy_filter(struct tcf_proto *tp, struct cls_fl_filter *f,
				 struct netlink_ext_ack *extack)
{
	struct tc_cls_flower_offload cls_flower = {};
	struct tcf_block *block = tp->chain->block;

	tc_cls_common_offload_init(&cls_flower.common, tp, f->flags, extack);
	cls_flower.command = TC_CLSFLOWER_DESTROY;
	cls_flower.cookie = (unsigned long) f;

	tc_setup_cb_call(block, &f->exts, TC_SETUP_CLSFLOWER,
			 &cls_flower, false);
	tcf_block_offload_dec(block, &f->flags);
}