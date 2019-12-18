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
struct TYPE_6__ {int insn_idx; int curframe; TYPE_1__** frame; scalar_t__ branches; } ;
struct bpf_verifier_state_list {struct bpf_verifier_state_list* next; TYPE_3__ state; } ;
struct bpf_verifier_state {int curframe; TYPE_2__** frame; } ;
struct bpf_verifier_env {int dummy; } ;
struct TYPE_5__ {scalar_t__ callsite; } ;
struct TYPE_4__ {scalar_t__ callsite; } ;

/* Variables and functions */
 int /*<<< orphan*/  clean_verifier_state (struct bpf_verifier_env*,TYPE_3__*) ; 
 struct bpf_verifier_state_list** explored_state (struct bpf_verifier_env*,int) ; 

__attribute__((used)) static void clean_live_states(struct bpf_verifier_env *env, int insn,
			      struct bpf_verifier_state *cur)
{
	struct bpf_verifier_state_list *sl;
	int i;

	sl = *explored_state(env, insn);
	while (sl) {
		if (sl->state.branches)
			goto next;
		if (sl->state.insn_idx != insn ||
		    sl->state.curframe != cur->curframe)
			goto next;
		for (i = 0; i <= cur->curframe; i++)
			if (sl->state.frame[i]->callsite != cur->frame[i]->callsite)
				goto next;
		clean_verifier_state(env, &sl->state);
next:
		sl = sl->next;
	}
}