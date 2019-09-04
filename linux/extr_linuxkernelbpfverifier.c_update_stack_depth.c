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
typedef  int u16 ;
struct bpf_verifier_env {TYPE_1__* subprog_info; } ;
struct bpf_func_state {size_t subprogno; } ;
struct TYPE_2__ {int stack_depth; } ;

/* Variables and functions */

__attribute__((used)) static int update_stack_depth(struct bpf_verifier_env *env,
			      const struct bpf_func_state *func,
			      int off)
{
	u16 stack = env->subprog_info[func->subprogno].stack_depth;

	if (stack >= -off)
		return 0;

	/* update known max for given subprogram */
	env->subprog_info[func->subprogno].stack_depth = -off;
	return 0;
}