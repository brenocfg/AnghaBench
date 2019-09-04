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
typedef  size_t u32 ;
struct bpf_verifier_state {size_t curframe; int /*<<< orphan*/  parent; struct bpf_func_state** frame; } ;
struct bpf_verifier_env {struct bpf_verifier_state* cur_state; } ;
struct bpf_reg_state {scalar_t__ type; int /*<<< orphan*/  live; } ;
struct bpf_func_state {struct bpf_reg_state* regs; } ;
typedef  enum reg_arg_type { ____Placeholder_reg_arg_type } reg_arg_type ;

/* Variables and functions */
 size_t BPF_REG_FP ; 
 int DST_OP ; 
 int EACCES ; 
 int EINVAL ; 
 size_t MAX_BPF_REG ; 
 scalar_t__ NOT_INIT ; 
 int /*<<< orphan*/  REG_LIVE_WRITTEN ; 
 int SRC_OP ; 
 int mark_reg_read (struct bpf_verifier_env*,struct bpf_verifier_state*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mark_reg_unknown (struct bpf_verifier_env*,struct bpf_reg_state*,size_t) ; 
 int /*<<< orphan*/  verbose (struct bpf_verifier_env*,char*,...) ; 

__attribute__((used)) static int check_reg_arg(struct bpf_verifier_env *env, u32 regno,
			 enum reg_arg_type t)
{
	struct bpf_verifier_state *vstate = env->cur_state;
	struct bpf_func_state *state = vstate->frame[vstate->curframe];
	struct bpf_reg_state *regs = state->regs;

	if (regno >= MAX_BPF_REG) {
		verbose(env, "R%d is invalid\n", regno);
		return -EINVAL;
	}

	if (t == SRC_OP) {
		/* check whether register used as source operand can be read */
		if (regs[regno].type == NOT_INIT) {
			verbose(env, "R%d !read_ok\n", regno);
			return -EACCES;
		}
		return mark_reg_read(env, vstate, vstate->parent, regno);
	} else {
		/* check whether register used as dest operand can be written to */
		if (regno == BPF_REG_FP) {
			verbose(env, "frame pointer is read only\n");
			return -EACCES;
		}
		regs[regno].live |= REG_LIVE_WRITTEN;
		if (t == DST_OP)
			mark_reg_unknown(env, regs, regno);
	}
	return 0;
}