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
struct bpf_verifier_state_list {int dummy; } ;
struct bpf_verifier_state {size_t curframe; struct bpf_func_state** frame; } ;
struct bpf_verifier_env {struct bpf_verifier_state_list** explored_states; struct bpf_verifier_state* cur_state; } ;
struct bpf_func_state {int callsite; } ;

/* Variables and functions */
 int state_htab_size (struct bpf_verifier_env*) ; 

__attribute__((used)) static struct bpf_verifier_state_list **explored_state(
					struct bpf_verifier_env *env,
					int idx)
{
	struct bpf_verifier_state *cur = env->cur_state;
	struct bpf_func_state *state = cur->frame[cur->curframe];

	return &env->explored_states[(idx ^ state->callsite) % state_htab_size(env)];
}