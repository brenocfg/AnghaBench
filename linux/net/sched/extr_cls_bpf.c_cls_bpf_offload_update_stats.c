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
struct tc_cls_bpf_offload {int /*<<< orphan*/  exts_integrated; int /*<<< orphan*/  name; int /*<<< orphan*/  prog; int /*<<< orphan*/ * exts; int /*<<< orphan*/  command; int /*<<< orphan*/  common; } ;
struct cls_bpf_prog {int /*<<< orphan*/  exts_integrated; int /*<<< orphan*/  bpf_name; int /*<<< orphan*/  filter; int /*<<< orphan*/  exts; int /*<<< orphan*/  gen_flags; } ;
struct TYPE_2__ {struct tcf_block* block; } ;

/* Variables and functions */
 int /*<<< orphan*/  TC_CLSBPF_STATS ; 
 int /*<<< orphan*/  TC_SETUP_CLSBPF ; 
 int /*<<< orphan*/  tc_cls_common_offload_init (int /*<<< orphan*/ *,struct tcf_proto*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tc_setup_cb_call (struct tcf_block*,int /*<<< orphan*/ ,struct tc_cls_bpf_offload*,int,int) ; 

__attribute__((used)) static void cls_bpf_offload_update_stats(struct tcf_proto *tp,
					 struct cls_bpf_prog *prog)
{
	struct tcf_block *block = tp->chain->block;
	struct tc_cls_bpf_offload cls_bpf = {};

	tc_cls_common_offload_init(&cls_bpf.common, tp, prog->gen_flags, NULL);
	cls_bpf.command = TC_CLSBPF_STATS;
	cls_bpf.exts = &prog->exts;
	cls_bpf.prog = prog->filter;
	cls_bpf.name = prog->bpf_name;
	cls_bpf.exts_integrated = prog->exts_integrated;

	tc_setup_cb_call(block, TC_SETUP_CLSBPF, &cls_bpf, false, true);
}