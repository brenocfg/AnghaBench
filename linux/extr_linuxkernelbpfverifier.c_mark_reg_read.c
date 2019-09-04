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
typedef  size_t u32 ;
struct bpf_verifier_state {size_t curframe; struct bpf_verifier_state* parent; TYPE_2__** frame; } ;
struct bpf_verifier_env {int dummy; } ;
struct TYPE_4__ {TYPE_1__* regs; } ;
struct TYPE_3__ {int live; } ;

/* Variables and functions */
 size_t BPF_REG_FP ; 
 int EFAULT ; 
 int REG_LIVE_READ ; 
 int REG_LIVE_WRITTEN ; 
 struct bpf_verifier_state* skip_callee (struct bpf_verifier_env*,struct bpf_verifier_state const*,struct bpf_verifier_state*,size_t) ; 

__attribute__((used)) static int mark_reg_read(struct bpf_verifier_env *env,
			 const struct bpf_verifier_state *state,
			 struct bpf_verifier_state *parent,
			 u32 regno)
{
	bool writes = parent == state->parent; /* Observe write marks */

	if (regno == BPF_REG_FP)
		/* We don't need to worry about FP liveness because it's read-only */
		return 0;

	while (parent) {
		/* if read wasn't screened by an earlier write ... */
		if (writes && state->frame[state->curframe]->regs[regno].live & REG_LIVE_WRITTEN)
			break;
		parent = skip_callee(env, state, parent, regno);
		if (!parent)
			return -EFAULT;
		/* ... then we depend on parent's value */
		parent->frame[parent->curframe]->regs[regno].live |= REG_LIVE_READ;
		state = parent;
		parent = state->parent;
		writes = true;
	}
	return 0;
}