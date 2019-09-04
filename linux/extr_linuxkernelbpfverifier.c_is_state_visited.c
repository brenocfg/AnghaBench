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
struct bpf_verifier_state_list {int /*<<< orphan*/  state; struct bpf_verifier_state_list* next; } ;
struct bpf_verifier_state {size_t curframe; struct bpf_func_state** frame; int /*<<< orphan*/ * parent; } ;
struct bpf_verifier_env {struct bpf_verifier_state_list** explored_states; int /*<<< orphan*/  allow_ptr_leaks; struct bpf_verifier_state* cur_state; } ;
struct bpf_func_state {int allocated_stack; TYPE_3__* stack; TYPE_1__* regs; } ;
struct TYPE_5__ {void* live; } ;
struct TYPE_6__ {TYPE_2__ spilled_ptr; } ;
struct TYPE_4__ {void* live; } ;

/* Variables and functions */
 int BPF_COMPLEXITY_LIMIT_STATES ; 
 int BPF_REG_FP ; 
 int BPF_REG_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* REG_LIVE_NONE ; 
 struct bpf_verifier_state_list* STATE_LIST_MARK ; 
 int copy_verifier_state (int /*<<< orphan*/ *,struct bpf_verifier_state*) ; 
 int /*<<< orphan*/  free_verifier_state (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct bpf_verifier_state_list*) ; 
 struct bpf_verifier_state_list* kzalloc (int,int /*<<< orphan*/ ) ; 
 int propagate_liveness (struct bpf_verifier_env*,int /*<<< orphan*/ *,struct bpf_verifier_state*) ; 
 scalar_t__ states_equal (struct bpf_verifier_env*,int /*<<< orphan*/ *,struct bpf_verifier_state*) ; 

__attribute__((used)) static int is_state_visited(struct bpf_verifier_env *env, int insn_idx)
{
	struct bpf_verifier_state_list *new_sl;
	struct bpf_verifier_state_list *sl;
	struct bpf_verifier_state *cur = env->cur_state;
	int i, j, err, states_cnt = 0;

	sl = env->explored_states[insn_idx];
	if (!sl)
		/* this 'insn_idx' instruction wasn't marked, so we will not
		 * be doing state search here
		 */
		return 0;

	while (sl != STATE_LIST_MARK) {
		if (states_equal(env, &sl->state, cur)) {
			/* reached equivalent register/stack state,
			 * prune the search.
			 * Registers read by the continuation are read by us.
			 * If we have any write marks in env->cur_state, they
			 * will prevent corresponding reads in the continuation
			 * from reaching our parent (an explored_state).  Our
			 * own state will get the read marks recorded, but
			 * they'll be immediately forgotten as we're pruning
			 * this state and will pop a new one.
			 */
			err = propagate_liveness(env, &sl->state, cur);
			if (err)
				return err;
			return 1;
		}
		sl = sl->next;
		states_cnt++;
	}

	if (!env->allow_ptr_leaks && states_cnt > BPF_COMPLEXITY_LIMIT_STATES)
		return 0;

	/* there were no equivalent states, remember current one.
	 * technically the current state is not proven to be safe yet,
	 * but it will either reach outer most bpf_exit (which means it's safe)
	 * or it will be rejected. Since there are no loops, we won't be
	 * seeing this tuple (frame[0].callsite, frame[1].callsite, .. insn_idx)
	 * again on the way to bpf_exit
	 */
	new_sl = kzalloc(sizeof(struct bpf_verifier_state_list), GFP_KERNEL);
	if (!new_sl)
		return -ENOMEM;

	/* add new state to the head of linked list */
	err = copy_verifier_state(&new_sl->state, cur);
	if (err) {
		free_verifier_state(&new_sl->state, false);
		kfree(new_sl);
		return err;
	}
	new_sl->next = env->explored_states[insn_idx];
	env->explored_states[insn_idx] = new_sl;
	/* connect new state to parentage chain */
	cur->parent = &new_sl->state;
	/* clear write marks in current state: the writes we did are not writes
	 * our child did, so they don't screen off its reads from us.
	 * (There are no read marks in current state, because reads always mark
	 * their parent and current state never has children yet.  Only
	 * explored_states can get read marks.)
	 */
	for (i = 0; i < BPF_REG_FP; i++)
		cur->frame[cur->curframe]->regs[i].live = REG_LIVE_NONE;

	/* all stack frames are accessible from callee, clear them all */
	for (j = 0; j <= cur->curframe; j++) {
		struct bpf_func_state *frame = cur->frame[j];

		for (i = 0; i < frame->allocated_stack / BPF_REG_SIZE; i++)
			frame->stack[i].spilled_ptr.live = REG_LIVE_NONE;
	}
	return 0;
}