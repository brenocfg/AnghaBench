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
struct btf_verifier_env {struct btf* btf; } ;
struct btf_type {int dummy; } ;
struct btf_array {size_t type; size_t nelems; } ;
struct btf {size_t* resolved_sizes; int /*<<< orphan*/ * resolved_ids; } ;

/* Variables and functions */
 struct btf_array* btf_type_array (struct btf_type const*) ; 
 struct btf_type* btf_type_id_resolve (struct btf*,size_t*) ; 
 struct btf_type* btf_type_id_size (struct btf*,size_t*,size_t*) ; 
 scalar_t__ btf_type_is_array (struct btf_type const*) ; 
 scalar_t__ btf_type_is_datasec (struct btf_type const*) ; 
 scalar_t__ btf_type_is_modifier (struct btf_type const*) ; 
 scalar_t__ btf_type_is_ptr (struct btf_type const*) ; 
 scalar_t__ btf_type_is_struct (struct btf_type const*) ; 
 scalar_t__ btf_type_is_var (struct btf_type const*) ; 
 int /*<<< orphan*/  env_type_is_resolved (struct btf_verifier_env*,size_t) ; 

__attribute__((used)) static bool btf_resolve_valid(struct btf_verifier_env *env,
			      const struct btf_type *t,
			      u32 type_id)
{
	struct btf *btf = env->btf;

	if (!env_type_is_resolved(env, type_id))
		return false;

	if (btf_type_is_struct(t) || btf_type_is_datasec(t))
		return !btf->resolved_ids[type_id] &&
		       !btf->resolved_sizes[type_id];

	if (btf_type_is_modifier(t) || btf_type_is_ptr(t) ||
	    btf_type_is_var(t)) {
		t = btf_type_id_resolve(btf, &type_id);
		return t &&
		       !btf_type_is_modifier(t) &&
		       !btf_type_is_var(t) &&
		       !btf_type_is_datasec(t);
	}

	if (btf_type_is_array(t)) {
		const struct btf_array *array = btf_type_array(t);
		const struct btf_type *elem_type;
		u32 elem_type_id = array->type;
		u32 elem_size;

		elem_type = btf_type_id_size(btf, &elem_type_id, &elem_size);
		return elem_type && !btf_type_is_modifier(elem_type) &&
			(array->nelems * elem_size ==
			 btf->resolved_sizes[type_id]);
	}

	return false;
}