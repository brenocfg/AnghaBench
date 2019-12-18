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
struct bpf_reg_state {int /*<<< orphan*/  umax_value; int /*<<< orphan*/  smax_value; } ;
struct bpf_call_arg_meta {int /*<<< orphan*/  msize_umax_value; int /*<<< orphan*/  msize_smax_value; } ;

/* Variables and functions */
 int BPF_FUNC_get_stack ; 
 int BPF_FUNC_probe_read_str ; 
 size_t BPF_REG_0 ; 
 int RET_INTEGER ; 
 int /*<<< orphan*/  __reg_bound_offset (struct bpf_reg_state*) ; 
 int /*<<< orphan*/  __reg_deduce_bounds (struct bpf_reg_state*) ; 

__attribute__((used)) static void do_refine_retval_range(struct bpf_reg_state *regs, int ret_type,
				   int func_id,
				   struct bpf_call_arg_meta *meta)
{
	struct bpf_reg_state *ret_reg = &regs[BPF_REG_0];

	if (ret_type != RET_INTEGER ||
	    (func_id != BPF_FUNC_get_stack &&
	     func_id != BPF_FUNC_probe_read_str))
		return;

	ret_reg->smax_value = meta->msize_smax_value;
	ret_reg->umax_value = meta->msize_umax_value;
	__reg_deduce_bounds(ret_reg);
	__reg_bound_offset(ret_reg);
}