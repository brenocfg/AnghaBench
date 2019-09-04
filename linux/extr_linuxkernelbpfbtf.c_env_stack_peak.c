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
struct resolve_vertex {int dummy; } ;
struct btf_verifier_env {int top_stack; struct resolve_vertex const* stack; } ;

/* Variables and functions */

__attribute__((used)) static const struct resolve_vertex *env_stack_peak(struct btf_verifier_env *env)
{
	return env->top_stack ? &env->stack[env->top_stack - 1] : NULL;
}