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
struct bpf_verifier_state {int speculative; } ;
struct bpf_verifier_stack_elem {int insn_idx; int prev_insn_idx; struct bpf_verifier_state st; struct bpf_verifier_stack_elem* next; } ;
struct bpf_verifier_env {scalar_t__ stack_size; struct bpf_verifier_state* cur_state; struct bpf_verifier_stack_elem* head; } ;

/* Variables and functions */
 scalar_t__ BPF_COMPLEXITY_LIMIT_STACK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int copy_verifier_state (struct bpf_verifier_state*,struct bpf_verifier_state*) ; 
 int /*<<< orphan*/  free_verifier_state (struct bpf_verifier_state*,int) ; 
 struct bpf_verifier_stack_elem* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pop_stack (struct bpf_verifier_env*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verbose (struct bpf_verifier_env*,char*) ; 

__attribute__((used)) static struct bpf_verifier_state *push_stack(struct bpf_verifier_env *env,
					     int insn_idx, int prev_insn_idx,
					     bool speculative)
{
	struct bpf_verifier_state *cur = env->cur_state;
	struct bpf_verifier_stack_elem *elem;
	int err;

	elem = kzalloc(sizeof(struct bpf_verifier_stack_elem), GFP_KERNEL);
	if (!elem)
		goto err;

	elem->insn_idx = insn_idx;
	elem->prev_insn_idx = prev_insn_idx;
	elem->next = env->head;
	env->head = elem;
	env->stack_size++;
	err = copy_verifier_state(&elem->st, cur);
	if (err)
		goto err;
	elem->st.speculative |= speculative;
	if (env->stack_size > BPF_COMPLEXITY_LIMIT_STACK) {
		verbose(env, "BPF program is too complex\n");
		goto err;
	}
	return &elem->st;
err:
	free_verifier_state(env->cur_state, true);
	env->cur_state = NULL;
	/* pop all elements and return */
	while (!pop_stack(env, NULL, NULL));
	return NULL;
}