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
typedef  size_t u32 ;
struct bpf_verifier_state {size_t curframe; struct bpf_func_state** frame; } ;
struct bpf_reg_state {size_t ref_obj_id; size_t id; } ;
struct bpf_func_state {struct bpf_reg_state* regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __mark_ptr_or_null_regs (struct bpf_func_state*,size_t,int) ; 
 int /*<<< orphan*/  release_reference_state (struct bpf_func_state*,size_t) ; 

__attribute__((used)) static void mark_ptr_or_null_regs(struct bpf_verifier_state *vstate, u32 regno,
				  bool is_null)
{
	struct bpf_func_state *state = vstate->frame[vstate->curframe];
	struct bpf_reg_state *regs = state->regs;
	u32 ref_obj_id = regs[regno].ref_obj_id;
	u32 id = regs[regno].id;
	int i;

	if (ref_obj_id && ref_obj_id == id && is_null)
		/* regs[regno] is in the " == NULL" branch.
		 * No one could have freed the reference state before
		 * doing the NULL check.
		 */
		WARN_ON_ONCE(release_reference_state(state, id));

	for (i = 0; i <= vstate->curframe; i++)
		__mark_ptr_or_null_regs(vstate->frame[i], id, is_null);
}