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
struct bpf_verifier_state {size_t curframe; struct bpf_func_state** frame; } ;
struct TYPE_2__ {int level; } ;
struct bpf_verifier_env {TYPE_1__ log; struct bpf_verifier_state* cur_state; } ;
struct bpf_reg_state {scalar_t__ type; } ;
struct bpf_func_state {int callsite; struct bpf_reg_state* regs; } ;

/* Variables and functions */
 int BPF_LOG_LEVEL ; 
 size_t BPF_REG_0 ; 
 int EINVAL ; 
 scalar_t__ PTR_TO_STACK ; 
 int /*<<< orphan*/  free_func_state (struct bpf_func_state*) ; 
 int /*<<< orphan*/  print_verifier_state (struct bpf_verifier_env*,struct bpf_func_state*) ; 
 int transfer_reference_state (struct bpf_func_state*,struct bpf_func_state*) ; 
 int /*<<< orphan*/  verbose (struct bpf_verifier_env*,char*,...) ; 

__attribute__((used)) static int prepare_func_exit(struct bpf_verifier_env *env, int *insn_idx)
{
	struct bpf_verifier_state *state = env->cur_state;
	struct bpf_func_state *caller, *callee;
	struct bpf_reg_state *r0;
	int err;

	callee = state->frame[state->curframe];
	r0 = &callee->regs[BPF_REG_0];
	if (r0->type == PTR_TO_STACK) {
		/* technically it's ok to return caller's stack pointer
		 * (or caller's caller's pointer) back to the caller,
		 * since these pointers are valid. Only current stack
		 * pointer will be invalid as soon as function exits,
		 * but let's be conservative
		 */
		verbose(env, "cannot return stack pointer to the caller\n");
		return -EINVAL;
	}

	state->curframe--;
	caller = state->frame[state->curframe];
	/* return to the caller whatever r0 had in the callee */
	caller->regs[BPF_REG_0] = *r0;

	/* Transfer references to the caller */
	err = transfer_reference_state(caller, callee);
	if (err)
		return err;

	*insn_idx = callee->callsite + 1;
	if (env->log.level & BPF_LOG_LEVEL) {
		verbose(env, "returning from callee:\n");
		print_verifier_state(env, callee);
		verbose(env, "to caller at %d:\n", *insn_idx);
		print_verifier_state(env, caller);
	}
	/* clear everything in the callee */
	free_func_state(callee);
	state->frame[state->curframe + 1] = NULL;
	return 0;
}