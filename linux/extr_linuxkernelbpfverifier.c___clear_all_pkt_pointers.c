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
struct bpf_verifier_env {int dummy; } ;
struct bpf_reg_state {int dummy; } ;
struct bpf_func_state {int allocated_stack; TYPE_1__* stack; struct bpf_reg_state* regs; } ;
struct TYPE_2__ {scalar_t__* slot_type; struct bpf_reg_state spilled_ptr; } ;

/* Variables and functions */
 int BPF_REG_SIZE ; 
 int MAX_BPF_REG ; 
 scalar_t__ STACK_SPILL ; 
 int /*<<< orphan*/  __mark_reg_unknown (struct bpf_reg_state*) ; 
 int /*<<< orphan*/  mark_reg_unknown (struct bpf_verifier_env*,struct bpf_reg_state*,int) ; 
 scalar_t__ reg_is_pkt_pointer_any (struct bpf_reg_state*) ; 

__attribute__((used)) static void __clear_all_pkt_pointers(struct bpf_verifier_env *env,
				     struct bpf_func_state *state)
{
	struct bpf_reg_state *regs = state->regs, *reg;
	int i;

	for (i = 0; i < MAX_BPF_REG; i++)
		if (reg_is_pkt_pointer_any(&regs[i]))
			mark_reg_unknown(env, regs, i);

	for (i = 0; i < state->allocated_stack / BPF_REG_SIZE; i++) {
		if (state->stack[i].slot_type[0] != STACK_SPILL)
			continue;
		reg = &state->stack[i].spilled_ptr;
		if (reg_is_pkt_pointer_any(reg))
			__mark_reg_unknown(reg);
	}
}