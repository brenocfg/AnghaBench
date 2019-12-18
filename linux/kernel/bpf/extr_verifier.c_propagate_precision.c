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
struct bpf_verifier_state {size_t curframe; struct bpf_func_state** frame; } ;
struct TYPE_4__ {int level; } ;
struct bpf_verifier_env {TYPE_2__ log; } ;
struct bpf_reg_state {scalar_t__ type; int /*<<< orphan*/  precise; } ;
struct bpf_func_state {int allocated_stack; TYPE_1__* stack; struct bpf_reg_state* regs; } ;
struct TYPE_3__ {scalar_t__* slot_type; struct bpf_reg_state spilled_ptr; } ;

/* Variables and functions */
 int BPF_LOG_LEVEL2 ; 
 int BPF_REG_FP ; 
 int BPF_REG_SIZE ; 
 scalar_t__ SCALAR_VALUE ; 
 scalar_t__ STACK_SPILL ; 
 int mark_chain_precision (struct bpf_verifier_env*,int) ; 
 int mark_chain_precision_stack (struct bpf_verifier_env*,int) ; 
 int /*<<< orphan*/  verbose (struct bpf_verifier_env*,char*,int) ; 

__attribute__((used)) static int propagate_precision(struct bpf_verifier_env *env,
			       const struct bpf_verifier_state *old)
{
	struct bpf_reg_state *state_reg;
	struct bpf_func_state *state;
	int i, err = 0;

	state = old->frame[old->curframe];
	state_reg = state->regs;
	for (i = 0; i < BPF_REG_FP; i++, state_reg++) {
		if (state_reg->type != SCALAR_VALUE ||
		    !state_reg->precise)
			continue;
		if (env->log.level & BPF_LOG_LEVEL2)
			verbose(env, "propagating r%d\n", i);
		err = mark_chain_precision(env, i);
		if (err < 0)
			return err;
	}

	for (i = 0; i < state->allocated_stack / BPF_REG_SIZE; i++) {
		if (state->stack[i].slot_type[0] != STACK_SPILL)
			continue;
		state_reg = &state->stack[i].spilled_ptr;
		if (state_reg->type != SCALAR_VALUE ||
		    !state_reg->precise)
			continue;
		if (env->log.level & BPF_LOG_LEVEL2)
			verbose(env, "propagating fp%d\n",
				(-i - 1) * BPF_REG_SIZE);
		err = mark_chain_precision_stack(env, i);
		if (err < 0)
			return err;
	}
	return 0;
}