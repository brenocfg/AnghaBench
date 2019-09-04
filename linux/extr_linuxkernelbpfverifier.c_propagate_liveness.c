#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bpf_verifier_state {size_t curframe; struct bpf_func_state** frame; } ;
struct bpf_verifier_env {int dummy; } ;
struct bpf_func_state {int allocated_stack; TYPE_3__* stack; TYPE_1__* regs; } ;
struct TYPE_5__ {int live; } ;
struct TYPE_6__ {TYPE_2__ spilled_ptr; } ;
struct TYPE_4__ {int live; } ;

/* Variables and functions */
 int BPF_REG_FP ; 
 int BPF_REG_SIZE ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EFAULT ; 
 int MAX_BPF_REG ; 
 int REG_LIVE_READ ; 
 int /*<<< orphan*/  WARN (int,char*,size_t,size_t) ; 
 int mark_reg_read (struct bpf_verifier_env*,struct bpf_verifier_state const*,struct bpf_verifier_state*,int) ; 
 int /*<<< orphan*/  mark_stack_slot_read (struct bpf_verifier_env*,struct bpf_verifier_state const*,struct bpf_verifier_state*,int,int) ; 

__attribute__((used)) static int propagate_liveness(struct bpf_verifier_env *env,
			      const struct bpf_verifier_state *vstate,
			      struct bpf_verifier_state *vparent)
{
	int i, frame, err = 0;
	struct bpf_func_state *state, *parent;

	if (vparent->curframe != vstate->curframe) {
		WARN(1, "propagate_live: parent frame %d current frame %d\n",
		     vparent->curframe, vstate->curframe);
		return -EFAULT;
	}
	/* Propagate read liveness of registers... */
	BUILD_BUG_ON(BPF_REG_FP + 1 != MAX_BPF_REG);
	/* We don't need to worry about FP liveness because it's read-only */
	for (i = 0; i < BPF_REG_FP; i++) {
		if (vparent->frame[vparent->curframe]->regs[i].live & REG_LIVE_READ)
			continue;
		if (vstate->frame[vstate->curframe]->regs[i].live & REG_LIVE_READ) {
			err = mark_reg_read(env, vstate, vparent, i);
			if (err)
				return err;
		}
	}

	/* ... and stack slots */
	for (frame = 0; frame <= vstate->curframe; frame++) {
		state = vstate->frame[frame];
		parent = vparent->frame[frame];
		for (i = 0; i < state->allocated_stack / BPF_REG_SIZE &&
			    i < parent->allocated_stack / BPF_REG_SIZE; i++) {
			if (parent->stack[i].spilled_ptr.live & REG_LIVE_READ)
				continue;
			if (state->stack[i].spilled_ptr.live & REG_LIVE_READ)
				mark_stack_slot_read(env, vstate, vparent, i, frame);
		}
	}
	return err;
}