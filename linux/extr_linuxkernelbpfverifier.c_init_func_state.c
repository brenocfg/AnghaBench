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
struct bpf_verifier_env {int dummy; } ;
struct bpf_func_state {int callsite; int frameno; int subprogno; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_reg_state (struct bpf_verifier_env*,struct bpf_func_state*) ; 

__attribute__((used)) static void init_func_state(struct bpf_verifier_env *env,
			    struct bpf_func_state *state,
			    int callsite, int frameno, int subprogno)
{
	state->callsite = callsite;
	state->frameno = frameno;
	state->subprogno = subprogno;
	init_reg_state(env, state);
}