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
typedef  scalar_t__ u32 ;
struct bpf_verifier_state {scalar_t__ curframe; struct bpf_verifier_state* parent; } ;
struct bpf_verifier_env {int dummy; } ;

/* Variables and functions */
 scalar_t__ BPF_REG_0 ; 
 scalar_t__ BPF_REG_1 ; 
 scalar_t__ BPF_REG_5 ; 
 scalar_t__ BPF_REG_6 ; 
 int /*<<< orphan*/  verbose (struct bpf_verifier_env*,char*,scalar_t__,scalar_t__,...) ; 

__attribute__((used)) static
struct bpf_verifier_state *skip_callee(struct bpf_verifier_env *env,
				       const struct bpf_verifier_state *state,
				       struct bpf_verifier_state *parent,
				       u32 regno)
{
	struct bpf_verifier_state *tmp = NULL;

	/* 'parent' could be a state of caller and
	 * 'state' could be a state of callee. In such case
	 * parent->curframe < state->curframe
	 * and it's ok for r1 - r5 registers
	 *
	 * 'parent' could be a callee's state after it bpf_exit-ed.
	 * In such case parent->curframe > state->curframe
	 * and it's ok for r0 only
	 */
	if (parent->curframe == state->curframe ||
	    (parent->curframe < state->curframe &&
	     regno >= BPF_REG_1 && regno <= BPF_REG_5) ||
	    (parent->curframe > state->curframe &&
	       regno == BPF_REG_0))
		return parent;

	if (parent->curframe > state->curframe &&
	    regno >= BPF_REG_6) {
		/* for callee saved regs we have to skip the whole chain
		 * of states that belong to callee and mark as LIVE_READ
		 * the registers before the call
		 */
		tmp = parent;
		while (tmp && tmp->curframe != state->curframe) {
			tmp = tmp->parent;
		}
		if (!tmp)
			goto bug;
		parent = tmp;
	} else {
		goto bug;
	}
	return parent;
bug:
	verbose(env, "verifier bug regno %d tmp %p\n", regno, tmp);
	verbose(env, "regno %d parent frame %d current frame %d\n",
		regno, parent->curframe, state->curframe);
	return NULL;
}