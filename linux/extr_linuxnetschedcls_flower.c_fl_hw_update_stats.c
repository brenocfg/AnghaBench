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
struct tcf_proto {TYPE_2__* chain; } ;
struct tcf_block {int dummy; } ;
struct tc_cls_flower_offload {unsigned long cookie; int /*<<< orphan*/  classid; int /*<<< orphan*/ * exts; int /*<<< orphan*/  command; int /*<<< orphan*/  common; } ;
struct TYPE_3__ {int /*<<< orphan*/  classid; } ;
struct cls_fl_filter {int /*<<< orphan*/  exts; TYPE_1__ res; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {struct tcf_block* block; } ;

/* Variables and functions */
 int /*<<< orphan*/  TC_CLSFLOWER_STATS ; 
 int /*<<< orphan*/  TC_SETUP_CLSFLOWER ; 
 int /*<<< orphan*/  tc_cls_common_offload_init (int /*<<< orphan*/ *,struct tcf_proto*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tc_setup_cb_call (struct tcf_block*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct tc_cls_flower_offload*,int) ; 

__attribute__((used)) static void fl_hw_update_stats(struct tcf_proto *tp, struct cls_fl_filter *f)
{
	struct tc_cls_flower_offload cls_flower = {};
	struct tcf_block *block = tp->chain->block;

	tc_cls_common_offload_init(&cls_flower.common, tp, f->flags, NULL);
	cls_flower.command = TC_CLSFLOWER_STATS;
	cls_flower.cookie = (unsigned long) f;
	cls_flower.exts = &f->exts;
	cls_flower.classid = f->res.classid;

	tc_setup_cb_call(block, &f->exts, TC_SETUP_CLSFLOWER,
			 &cls_flower, false);
}