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
struct resolve_vertex {size_t type_id; scalar_t__ next_member; struct btf_type const* t; } ;
struct btf_verifier_env {scalar_t__ top_stack; scalar_t__* visit_states; scalar_t__ resolve_mode; struct resolve_vertex* stack; } ;
struct btf_type {int dummy; } ;

/* Variables and functions */
 int E2BIG ; 
 int EEXIST ; 
 scalar_t__ MAX_RESOLVE_DEPTH ; 
 scalar_t__ NOT_VISITED ; 
 scalar_t__ RESOLVE_PTR ; 
 scalar_t__ RESOLVE_STRUCT_OR_ARRAY ; 
 scalar_t__ RESOLVE_TBD ; 
 scalar_t__ VISITED ; 
 scalar_t__ btf_type_is_array (struct btf_type const*) ; 
 scalar_t__ btf_type_is_ptr (struct btf_type const*) ; 
 scalar_t__ btf_type_is_struct (struct btf_type const*) ; 

__attribute__((used)) static int env_stack_push(struct btf_verifier_env *env,
			  const struct btf_type *t, u32 type_id)
{
	struct resolve_vertex *v;

	if (env->top_stack == MAX_RESOLVE_DEPTH)
		return -E2BIG;

	if (env->visit_states[type_id] != NOT_VISITED)
		return -EEXIST;

	env->visit_states[type_id] = VISITED;

	v = &env->stack[env->top_stack++];
	v->t = t;
	v->type_id = type_id;
	v->next_member = 0;

	if (env->resolve_mode == RESOLVE_TBD) {
		if (btf_type_is_ptr(t))
			env->resolve_mode = RESOLVE_PTR;
		else if (btf_type_is_struct(t) || btf_type_is_array(t))
			env->resolve_mode = RESOLVE_STRUCT_OR_ARRAY;
	}

	return 0;
}