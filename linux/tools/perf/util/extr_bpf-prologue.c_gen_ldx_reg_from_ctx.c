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
struct bpf_insn_pos {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_DW ; 
 int /*<<< orphan*/  BPF_LDX_MEM (int /*<<< orphan*/ ,int,int,int) ; 
 int check_pos (struct bpf_insn_pos*) ; 
 int /*<<< orphan*/  ins (int /*<<< orphan*/ ,struct bpf_insn_pos*) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 int regs_query_register_offset (char const*) ; 

__attribute__((used)) static int
gen_ldx_reg_from_ctx(struct bpf_insn_pos *pos, int ctx_reg,
		     const char *reg, int target_reg)
{
	int offset = regs_query_register_offset(reg);

	if (offset < 0) {
		pr_err("bpf: prologue: failed to get register %s\n",
		       reg);
		return offset;
	}
	ins(BPF_LDX_MEM(BPF_DW, target_reg, ctx_reg, offset), pos);

	return check_pos(pos);
}