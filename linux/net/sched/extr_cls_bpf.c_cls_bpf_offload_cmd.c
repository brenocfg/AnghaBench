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
struct tc_cls_bpf_offload {int /*<<< orphan*/  exts_integrated; int /*<<< orphan*/  name; int /*<<< orphan*/ * oldprog; int /*<<< orphan*/ * prog; int /*<<< orphan*/ * exts; int /*<<< orphan*/  command; int /*<<< orphan*/  common; } ;
struct netlink_ext_ack {int dummy; } ;
struct cls_bpf_prog {int gen_flags; int /*<<< orphan*/  in_hw_count; int /*<<< orphan*/  exts_integrated; int /*<<< orphan*/  bpf_name; int /*<<< orphan*/ * filter; int /*<<< orphan*/  exts; } ;
struct TYPE_2__ {struct tcf_block* block; } ;

/* Variables and functions */
 int EINVAL ; 
 int TCA_CLS_FLAGS_IN_HW ; 
 int /*<<< orphan*/  TC_CLSBPF_OFFLOAD ; 
 int /*<<< orphan*/  TC_SETUP_CLSBPF ; 
 int /*<<< orphan*/  tc_cls_common_offload_init (int /*<<< orphan*/ *,struct tcf_proto*,int,struct netlink_ext_ack*) ; 
 int tc_setup_cb_add (struct tcf_block*,struct tcf_proto*,int /*<<< orphan*/ ,struct tc_cls_bpf_offload*,int,int*,int /*<<< orphan*/ *,int) ; 
 int tc_setup_cb_destroy (struct tcf_block*,struct tcf_proto*,int /*<<< orphan*/ ,struct tc_cls_bpf_offload*,int,int*,int /*<<< orphan*/ *,int) ; 
 int tc_setup_cb_replace (struct tcf_block*,struct tcf_proto*,int /*<<< orphan*/ ,struct tc_cls_bpf_offload*,int,int*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ tc_skip_sw (int) ; 

__attribute__((used)) static int cls_bpf_offload_cmd(struct tcf_proto *tp, struct cls_bpf_prog *prog,
			       struct cls_bpf_prog *oldprog,
			       struct netlink_ext_ack *extack)
{
	struct tcf_block *block = tp->chain->block;
	struct tc_cls_bpf_offload cls_bpf = {};
	struct cls_bpf_prog *obj;
	bool skip_sw;
	int err;

	skip_sw = prog && tc_skip_sw(prog->gen_flags);
	obj = prog ?: oldprog;

	tc_cls_common_offload_init(&cls_bpf.common, tp, obj->gen_flags, extack);
	cls_bpf.command = TC_CLSBPF_OFFLOAD;
	cls_bpf.exts = &obj->exts;
	cls_bpf.prog = prog ? prog->filter : NULL;
	cls_bpf.oldprog = oldprog ? oldprog->filter : NULL;
	cls_bpf.name = obj->bpf_name;
	cls_bpf.exts_integrated = obj->exts_integrated;

	if (oldprog && prog)
		err = tc_setup_cb_replace(block, tp, TC_SETUP_CLSBPF, &cls_bpf,
					  skip_sw, &oldprog->gen_flags,
					  &oldprog->in_hw_count,
					  &prog->gen_flags, &prog->in_hw_count,
					  true);
	else if (prog)
		err = tc_setup_cb_add(block, tp, TC_SETUP_CLSBPF, &cls_bpf,
				      skip_sw, &prog->gen_flags,
				      &prog->in_hw_count, true);
	else
		err = tc_setup_cb_destroy(block, tp, TC_SETUP_CLSBPF, &cls_bpf,
					  skip_sw, &oldprog->gen_flags,
					  &oldprog->in_hw_count, true);

	if (prog && err) {
		cls_bpf_offload_cmd(tp, oldprog, prog, extack);
		return err;
	}

	if (prog && skip_sw && !(prog->gen_flags & TCA_CLS_FLAGS_IN_HW))
		return -EINVAL;

	return 0;
}