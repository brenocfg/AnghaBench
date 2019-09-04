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
struct tc_cls_matchall_offload {unsigned long cookie; int /*<<< orphan*/ * exts; int /*<<< orphan*/  command; int /*<<< orphan*/  common; } ;
struct netlink_ext_ack {int dummy; } ;
struct cls_mall_head {int flags; int in_hw_count; int /*<<< orphan*/  exts; } ;
struct TYPE_2__ {struct tcf_block* block; } ;

/* Variables and functions */
 int EINVAL ; 
 int TCA_CLS_FLAGS_IN_HW ; 
 int /*<<< orphan*/  TC_CLSMATCHALL_REPLACE ; 
 int /*<<< orphan*/  TC_SETUP_CLSMATCHALL ; 
 int /*<<< orphan*/  mall_destroy_hw_filter (struct tcf_proto*,struct cls_mall_head*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tc_cls_common_offload_init (int /*<<< orphan*/ *,struct tcf_proto*,int,struct netlink_ext_ack*) ; 
 int tc_setup_cb_call (struct tcf_block*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct tc_cls_matchall_offload*,int) ; 
 int tc_skip_sw (int) ; 
 int /*<<< orphan*/  tcf_block_offload_inc (struct tcf_block*,int*) ; 

__attribute__((used)) static int mall_replace_hw_filter(struct tcf_proto *tp,
				  struct cls_mall_head *head,
				  unsigned long cookie,
				  struct netlink_ext_ack *extack)
{
	struct tc_cls_matchall_offload cls_mall = {};
	struct tcf_block *block = tp->chain->block;
	bool skip_sw = tc_skip_sw(head->flags);
	int err;

	tc_cls_common_offload_init(&cls_mall.common, tp, head->flags, extack);
	cls_mall.command = TC_CLSMATCHALL_REPLACE;
	cls_mall.exts = &head->exts;
	cls_mall.cookie = cookie;

	err = tc_setup_cb_call(block, NULL, TC_SETUP_CLSMATCHALL,
			       &cls_mall, skip_sw);
	if (err < 0) {
		mall_destroy_hw_filter(tp, head, cookie, NULL);
		return err;
	} else if (err > 0) {
		head->in_hw_count = err;
		tcf_block_offload_inc(block, &head->flags);
	}

	if (skip_sw && !(head->flags & TCA_CLS_FLAGS_IN_HW))
		return -EINVAL;

	return 0;
}