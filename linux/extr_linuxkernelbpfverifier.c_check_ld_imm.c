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
typedef  int u64 ;
typedef  int u32 ;
struct bpf_verifier_env {int dummy; } ;
struct bpf_reg_state {int /*<<< orphan*/  map_ptr; int /*<<< orphan*/  type; } ;
struct bpf_insn {scalar_t__ off; size_t dst_reg; scalar_t__ src_reg; scalar_t__ imm; int /*<<< orphan*/  code; } ;

/* Variables and functions */
 scalar_t__ BPF_DW ; 
 scalar_t__ BPF_PSEUDO_MAP_FD ; 
 scalar_t__ BPF_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CONST_PTR_TO_MAP ; 
 int /*<<< orphan*/  DST_OP ; 
 int EINVAL ; 
 int /*<<< orphan*/  SCALAR_VALUE ; 
 int /*<<< orphan*/  __mark_reg_known (struct bpf_reg_state*,int) ; 
 int check_reg_arg (struct bpf_verifier_env*,size_t,int /*<<< orphan*/ ) ; 
 struct bpf_reg_state* cur_regs (struct bpf_verifier_env*) ; 
 int /*<<< orphan*/  ld_imm64_to_map_ptr (struct bpf_insn*) ; 
 int /*<<< orphan*/  verbose (struct bpf_verifier_env*,char*) ; 

__attribute__((used)) static int check_ld_imm(struct bpf_verifier_env *env, struct bpf_insn *insn)
{
	struct bpf_reg_state *regs = cur_regs(env);
	int err;

	if (BPF_SIZE(insn->code) != BPF_DW) {
		verbose(env, "invalid BPF_LD_IMM insn\n");
		return -EINVAL;
	}
	if (insn->off != 0) {
		verbose(env, "BPF_LD_IMM64 uses reserved fields\n");
		return -EINVAL;
	}

	err = check_reg_arg(env, insn->dst_reg, DST_OP);
	if (err)
		return err;

	if (insn->src_reg == 0) {
		u64 imm = ((u64)(insn + 1)->imm << 32) | (u32)insn->imm;

		regs[insn->dst_reg].type = SCALAR_VALUE;
		__mark_reg_known(&regs[insn->dst_reg], imm);
		return 0;
	}

	/* replace_map_fd_with_map_ptr() should have caught bad ld_imm64 */
	BUG_ON(insn->src_reg != BPF_PSEUDO_MAP_FD);

	regs[insn->dst_reg].type = CONST_PTR_TO_MAP;
	regs[insn->dst_reg].map_ptr = ld_imm64_to_map_ptr(insn);
	return 0;
}