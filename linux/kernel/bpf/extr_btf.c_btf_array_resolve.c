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
typedef  int u32 ;
struct resolve_vertex {int /*<<< orphan*/  t; } ;
struct btf_verifier_env {struct btf* btf; } ;
struct btf_type {int dummy; } ;
struct btf_array {int index_type; int type; int nelems; } ;
struct btf {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int U32_MAX ; 
 struct btf_array* btf_type_array (int /*<<< orphan*/ ) ; 
 struct btf_type* btf_type_by_id (struct btf*,int) ; 
 struct btf_type* btf_type_id_size (struct btf*,int*,int*) ; 
 int /*<<< orphan*/  btf_type_int_is_regular (struct btf_type const*) ; 
 scalar_t__ btf_type_is_int (struct btf_type const*) ; 
 scalar_t__ btf_type_is_resolve_source_only (struct btf_type const*) ; 
 scalar_t__ btf_type_nosize_or_null (struct btf_type const*) ; 
 int /*<<< orphan*/  btf_verifier_log_type (struct btf_verifier_env*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  env_stack_pop_resolved (struct btf_verifier_env*,int,int) ; 
 int env_stack_push (struct btf_verifier_env*,struct btf_type const*,int) ; 
 int /*<<< orphan*/  env_type_is_resolve_sink (struct btf_verifier_env*,struct btf_type const*) ; 
 int /*<<< orphan*/  env_type_is_resolved (struct btf_verifier_env*,int) ; 

__attribute__((used)) static int btf_array_resolve(struct btf_verifier_env *env,
			     const struct resolve_vertex *v)
{
	const struct btf_array *array = btf_type_array(v->t);
	const struct btf_type *elem_type, *index_type;
	u32 elem_type_id, index_type_id;
	struct btf *btf = env->btf;
	u32 elem_size;

	/* Check array->index_type */
	index_type_id = array->index_type;
	index_type = btf_type_by_id(btf, index_type_id);
	if (btf_type_nosize_or_null(index_type) ||
	    btf_type_is_resolve_source_only(index_type)) {
		btf_verifier_log_type(env, v->t, "Invalid index");
		return -EINVAL;
	}

	if (!env_type_is_resolve_sink(env, index_type) &&
	    !env_type_is_resolved(env, index_type_id))
		return env_stack_push(env, index_type, index_type_id);

	index_type = btf_type_id_size(btf, &index_type_id, NULL);
	if (!index_type || !btf_type_is_int(index_type) ||
	    !btf_type_int_is_regular(index_type)) {
		btf_verifier_log_type(env, v->t, "Invalid index");
		return -EINVAL;
	}

	/* Check array->type */
	elem_type_id = array->type;
	elem_type = btf_type_by_id(btf, elem_type_id);
	if (btf_type_nosize_or_null(elem_type) ||
	    btf_type_is_resolve_source_only(elem_type)) {
		btf_verifier_log_type(env, v->t,
				      "Invalid elem");
		return -EINVAL;
	}

	if (!env_type_is_resolve_sink(env, elem_type) &&
	    !env_type_is_resolved(env, elem_type_id))
		return env_stack_push(env, elem_type, elem_type_id);

	elem_type = btf_type_id_size(btf, &elem_type_id, &elem_size);
	if (!elem_type) {
		btf_verifier_log_type(env, v->t, "Invalid elem");
		return -EINVAL;
	}

	if (btf_type_is_int(elem_type) && !btf_type_int_is_regular(elem_type)) {
		btf_verifier_log_type(env, v->t, "Invalid array of int");
		return -EINVAL;
	}

	if (array->nelems && elem_size > U32_MAX / array->nelems) {
		btf_verifier_log_type(env, v->t,
				      "Array size overflows U32_MAX");
		return -EINVAL;
	}

	env_stack_pop_resolved(env, elem_type_id, elem_size * array->nelems);

	return 0;
}