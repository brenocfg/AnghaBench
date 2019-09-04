#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct bpf_verifier_state {size_t curframe; int /*<<< orphan*/  parent; struct bpf_func_state** frame; } ;
struct bpf_verifier_env {struct bpf_verifier_state* cur_state; } ;
struct bpf_func_state {int allocated_stack; TYPE_2__* regs; int /*<<< orphan*/  frameno; TYPE_1__* stack; } ;
struct TYPE_5__ {int /*<<< orphan*/  live; } ;
struct TYPE_4__ {TYPE_2__ spilled_ptr; scalar_t__* slot_type; } ;

/* Variables and functions */
 int BPF_REG_SIZE ; 
 int EACCES ; 
 int /*<<< orphan*/  REG_LIVE_WRITTEN ; 
 scalar_t__ STACK_MISC ; 
 scalar_t__ STACK_SPILL ; 
 scalar_t__ STACK_ZERO ; 
 int /*<<< orphan*/  __mark_reg_const_zero (TYPE_2__*) ; 
 int /*<<< orphan*/  mark_reg_unknown (struct bpf_verifier_env*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  mark_stack_slot_read (struct bpf_verifier_env*,struct bpf_verifier_state*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (struct bpf_verifier_env*,char*,...) ; 

__attribute__((used)) static int check_stack_read(struct bpf_verifier_env *env,
			    struct bpf_func_state *reg_state /* func where register points to */,
			    int off, int size, int value_regno)
{
	struct bpf_verifier_state *vstate = env->cur_state;
	struct bpf_func_state *state = vstate->frame[vstate->curframe];
	int i, slot = -off - 1, spi = slot / BPF_REG_SIZE;
	u8 *stype;

	if (reg_state->allocated_stack <= slot) {
		verbose(env, "invalid read from stack off %d+0 size %d\n",
			off, size);
		return -EACCES;
	}
	stype = reg_state->stack[spi].slot_type;

	if (stype[0] == STACK_SPILL) {
		if (size != BPF_REG_SIZE) {
			verbose(env, "invalid size of register spill\n");
			return -EACCES;
		}
		for (i = 1; i < BPF_REG_SIZE; i++) {
			if (stype[(slot - i) % BPF_REG_SIZE] != STACK_SPILL) {
				verbose(env, "corrupted spill memory\n");
				return -EACCES;
			}
		}

		if (value_regno >= 0) {
			/* restore register state from stack */
			state->regs[value_regno] = reg_state->stack[spi].spilled_ptr;
			/* mark reg as written since spilled pointer state likely
			 * has its liveness marks cleared by is_state_visited()
			 * which resets stack/reg liveness for state transitions
			 */
			state->regs[value_regno].live |= REG_LIVE_WRITTEN;
		}
		mark_stack_slot_read(env, vstate, vstate->parent, spi,
				     reg_state->frameno);
		return 0;
	} else {
		int zeros = 0;

		for (i = 0; i < size; i++) {
			if (stype[(slot - i) % BPF_REG_SIZE] == STACK_MISC)
				continue;
			if (stype[(slot - i) % BPF_REG_SIZE] == STACK_ZERO) {
				zeros++;
				continue;
			}
			verbose(env, "invalid read from stack off %d+%d size %d\n",
				off, i, size);
			return -EACCES;
		}
		mark_stack_slot_read(env, vstate, vstate->parent, spi,
				     reg_state->frameno);
		if (value_regno >= 0) {
			if (zeros == size) {
				/* any size read into register is zero extended,
				 * so the whole register == const_zero
				 */
				__mark_reg_const_zero(&state->regs[value_regno]);
			} else {
				/* have read misc data from the stack */
				mark_reg_unknown(env, state->regs, value_regno);
			}
			state->regs[value_regno].live |= REG_LIVE_WRITTEN;
		}
		return 0;
	}
}