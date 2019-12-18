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
struct bpf_verifier_state {int curframe; struct bpf_func_state** frame; struct bpf_verifier_state* parent; } ;
struct bpf_verifier_env {int dummy; } ;
struct bpf_reg_state {scalar_t__ type; int precise; } ;
struct bpf_func_state {int allocated_stack; TYPE_1__* stack; struct bpf_reg_state* regs; } ;
struct TYPE_2__ {scalar_t__* slot_type; struct bpf_reg_state spilled_ptr; } ;

/* Variables and functions */
 int BPF_REG_FP ; 
 int BPF_REG_SIZE ; 
 scalar_t__ SCALAR_VALUE ; 
 scalar_t__ STACK_SPILL ; 

__attribute__((used)) static void mark_all_scalars_precise(struct bpf_verifier_env *env,
				     struct bpf_verifier_state *st)
{
	struct bpf_func_state *func;
	struct bpf_reg_state *reg;
	int i, j;

	/* big hammer: mark all scalars precise in this path.
	 * pop_stack may still get !precise scalars.
	 */
	for (; st; st = st->parent)
		for (i = 0; i <= st->curframe; i++) {
			func = st->frame[i];
			for (j = 0; j < BPF_REG_FP; j++) {
				reg = &func->regs[j];
				if (reg->type != SCALAR_VALUE)
					continue;
				reg->precise = true;
			}
			for (j = 0; j < func->allocated_stack / BPF_REG_SIZE; j++) {
				if (func->stack[j].slot_type[0] != STACK_SPILL)
					continue;
				reg = &func->stack[j].spilled_ptr;
				if (reg->type != SCALAR_VALUE)
					continue;
				reg->precise = true;
			}
		}
}