#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bpf_verifier_env {int dummy; } ;
struct bpf_func_state {int acquired_refs; TYPE_1__* refs; } ;
struct TYPE_2__ {int /*<<< orphan*/  insn_idx; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EINVAL ; 
 struct bpf_func_state* cur_func (struct bpf_verifier_env*) ; 
 int /*<<< orphan*/  verbose (struct bpf_verifier_env*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_reference_leak(struct bpf_verifier_env *env)
{
	struct bpf_func_state *state = cur_func(env);
	int i;

	for (i = 0; i < state->acquired_refs; i++) {
		verbose(env, "Unreleased reference id=%d alloc_insn=%d\n",
			state->refs[i].id, state->refs[i].insn_idx);
	}
	return state->acquired_refs ? -EINVAL : 0;
}