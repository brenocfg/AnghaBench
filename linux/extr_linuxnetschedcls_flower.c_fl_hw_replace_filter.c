#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tcf_proto {TYPE_1__* chain; } ;
struct tcf_block {int dummy; } ;
struct tc_cls_flower_offload {unsigned long cookie; int /*<<< orphan*/  classid; int /*<<< orphan*/ * exts; int /*<<< orphan*/ * key; int /*<<< orphan*/ * mask; int /*<<< orphan*/ * dissector; int /*<<< orphan*/  command; int /*<<< orphan*/  common; } ;
struct netlink_ext_ack {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  classid; } ;
struct cls_fl_filter {int flags; int in_hw_count; int /*<<< orphan*/  exts; TYPE_3__ res; int /*<<< orphan*/  mkey; TYPE_2__* mask; } ;
struct TYPE_5__ {int /*<<< orphan*/  key; int /*<<< orphan*/  dissector; } ;
struct TYPE_4__ {struct tcf_block* block; } ;

/* Variables and functions */
 int EINVAL ; 
 int TCA_CLS_FLAGS_IN_HW ; 
 int /*<<< orphan*/  TC_CLSFLOWER_REPLACE ; 
 int /*<<< orphan*/  TC_SETUP_CLSFLOWER ; 
 int /*<<< orphan*/  fl_hw_destroy_filter (struct tcf_proto*,struct cls_fl_filter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tc_cls_common_offload_init (int /*<<< orphan*/ *,struct tcf_proto*,int,struct netlink_ext_ack*) ; 
 int tc_setup_cb_call (struct tcf_block*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct tc_cls_flower_offload*,int) ; 
 int tc_skip_sw (int) ; 
 int /*<<< orphan*/  tcf_block_offload_inc (struct tcf_block*,int*) ; 

__attribute__((used)) static int fl_hw_replace_filter(struct tcf_proto *tp,
				struct cls_fl_filter *f,
				struct netlink_ext_ack *extack)
{
	struct tc_cls_flower_offload cls_flower = {};
	struct tcf_block *block = tp->chain->block;
	bool skip_sw = tc_skip_sw(f->flags);
	int err;

	tc_cls_common_offload_init(&cls_flower.common, tp, f->flags, extack);
	cls_flower.command = TC_CLSFLOWER_REPLACE;
	cls_flower.cookie = (unsigned long) f;
	cls_flower.dissector = &f->mask->dissector;
	cls_flower.mask = &f->mask->key;
	cls_flower.key = &f->mkey;
	cls_flower.exts = &f->exts;
	cls_flower.classid = f->res.classid;

	err = tc_setup_cb_call(block, &f->exts, TC_SETUP_CLSFLOWER,
			       &cls_flower, skip_sw);
	if (err < 0) {
		fl_hw_destroy_filter(tp, f, NULL);
		return err;
	} else if (err > 0) {
		f->in_hw_count = err;
		tcf_block_offload_inc(block, &f->flags);
	}

	if (skip_sw && !(f->flags & TCA_CLS_FLAGS_IN_HW))
		return -EINVAL;

	return 0;
}