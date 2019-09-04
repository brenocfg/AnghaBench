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
typedef  size_t u32 ;
struct bpf_verifier_state {size_t curframe; struct bpf_func_state** frame; } ;
struct bpf_reg_state {size_t id; } ;
struct bpf_func_state {int allocated_stack; TYPE_1__* stack; struct bpf_reg_state* regs; } ;
struct TYPE_2__ {scalar_t__* slot_type; struct bpf_reg_state spilled_ptr; } ;

/* Variables and functions */
 int BPF_REG_SIZE ; 
 int MAX_BPF_REG ; 
 scalar_t__ STACK_SPILL ; 
 int /*<<< orphan*/  mark_map_reg (struct bpf_reg_state*,int,size_t,int) ; 

__attribute__((used)) static void mark_map_regs(struct bpf_verifier_state *vstate, u32 regno,
			  bool is_null)
{
	struct bpf_func_state *state = vstate->frame[vstate->curframe];
	struct bpf_reg_state *regs = state->regs;
	u32 id = regs[regno].id;
	int i, j;

	for (i = 0; i < MAX_BPF_REG; i++)
		mark_map_reg(regs, i, id, is_null);

	for (j = 0; j <= vstate->curframe; j++) {
		state = vstate->frame[j];
		for (i = 0; i < state->allocated_stack / BPF_REG_SIZE; i++) {
			if (state->stack[i].slot_type[0] != STACK_SPILL)
				continue;
			mark_map_reg(&state->stack[i].spilled_ptr, 0, id, is_null);
		}
	}
}