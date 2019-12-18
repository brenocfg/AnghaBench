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
struct probe_trace_arg {int /*<<< orphan*/  value; } ;
struct bpf_insn_pos {int dummy; } ;

/* Variables and functions */
 scalar_t__ BPF_PROLOGUE_START_ARG_REG ; 
 int /*<<< orphan*/  BPF_REG_1 ; 
 int check_pos (struct bpf_insn_pos*) ; 
 int gen_ldx_reg_from_ctx (struct bpf_insn_pos*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
gen_prologue_fastpath(struct bpf_insn_pos *pos,
		      struct probe_trace_arg *args, int nargs)
{
	int i, err = 0;

	for (i = 0; i < nargs; i++) {
		err = gen_ldx_reg_from_ctx(pos, BPF_REG_1, args[i].value,
					   BPF_PROLOGUE_START_ARG_REG + i);
		if (err)
			goto errout;
	}

	return check_pos(pos);
errout:
	return err;
}