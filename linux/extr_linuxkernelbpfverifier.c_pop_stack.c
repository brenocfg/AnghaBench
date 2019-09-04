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
struct bpf_verifier_state {int dummy; } ;
struct bpf_verifier_stack_elem {int insn_idx; int prev_insn_idx; int /*<<< orphan*/  st; struct bpf_verifier_stack_elem* next; } ;
struct bpf_verifier_env {int /*<<< orphan*/  stack_size; struct bpf_verifier_stack_elem* head; struct bpf_verifier_state* cur_state; } ;

/* Variables and functions */
 int ENOENT ; 
 int copy_verifier_state (struct bpf_verifier_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_verifier_state (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct bpf_verifier_stack_elem*) ; 

__attribute__((used)) static int pop_stack(struct bpf_verifier_env *env, int *prev_insn_idx,
		     int *insn_idx)
{
	struct bpf_verifier_state *cur = env->cur_state;
	struct bpf_verifier_stack_elem *elem, *head = env->head;
	int err;

	if (env->head == NULL)
		return -ENOENT;

	if (cur) {
		err = copy_verifier_state(cur, &head->st);
		if (err)
			return err;
	}
	if (insn_idx)
		*insn_idx = head->insn_idx;
	if (prev_insn_idx)
		*prev_insn_idx = head->prev_insn_idx;
	elem = head->next;
	free_verifier_state(&head->st, false);
	kfree(head);
	env->head = elem;
	env->stack_size--;
	return 0;
}