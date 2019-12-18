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
struct bpf_verifier_env {int dummy; } ;
struct bpf_reg_state {int /*<<< orphan*/  type; int /*<<< orphan*/  frameno; int /*<<< orphan*/  subreg_def; int /*<<< orphan*/ * parent; int /*<<< orphan*/  live; } ;
struct bpf_func_state {int /*<<< orphan*/  frameno; struct bpf_reg_state* regs; } ;

/* Variables and functions */
 size_t BPF_REG_1 ; 
 size_t BPF_REG_FP ; 
 int /*<<< orphan*/  DEF_NOT_SUBREG ; 
 int MAX_BPF_REG ; 
 int /*<<< orphan*/  PTR_TO_CTX ; 
 int /*<<< orphan*/  PTR_TO_STACK ; 
 int /*<<< orphan*/  REG_LIVE_NONE ; 
 int /*<<< orphan*/  mark_reg_known_zero (struct bpf_verifier_env*,struct bpf_reg_state*,size_t) ; 
 int /*<<< orphan*/  mark_reg_not_init (struct bpf_verifier_env*,struct bpf_reg_state*,int) ; 

__attribute__((used)) static void init_reg_state(struct bpf_verifier_env *env,
			   struct bpf_func_state *state)
{
	struct bpf_reg_state *regs = state->regs;
	int i;

	for (i = 0; i < MAX_BPF_REG; i++) {
		mark_reg_not_init(env, regs, i);
		regs[i].live = REG_LIVE_NONE;
		regs[i].parent = NULL;
		regs[i].subreg_def = DEF_NOT_SUBREG;
	}

	/* frame pointer */
	regs[BPF_REG_FP].type = PTR_TO_STACK;
	mark_reg_known_zero(env, regs, BPF_REG_FP);
	regs[BPF_REG_FP].frameno = state->frameno;

	/* 1st arg to a function */
	regs[BPF_REG_1].type = PTR_TO_CTX;
	mark_reg_known_zero(env, regs, BPF_REG_1);
}