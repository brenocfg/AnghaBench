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
typedef  int /*<<< orphan*/  u32 ;
struct resolve_vertex {struct btf_type* t; } ;
struct btf_verifier_env {struct btf* btf; } ;
struct btf_type {int /*<<< orphan*/  type; } ;
struct btf {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct btf_type* btf_type_by_id (struct btf*,int /*<<< orphan*/ ) ; 
 struct btf_type* btf_type_id_resolve (struct btf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btf_type_id_size (struct btf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btf_type_is_func_proto (struct btf_type const*) ; 
 int /*<<< orphan*/  btf_type_is_fwd (struct btf_type const*) ; 
 scalar_t__ btf_type_is_resolve_source_only (struct btf_type const*) ; 
 int /*<<< orphan*/  btf_type_is_void (struct btf_type const*) ; 
 int /*<<< orphan*/  btf_verifier_log_type (struct btf_verifier_env*,struct btf_type*,char*) ; 
 int /*<<< orphan*/  env_stack_pop_resolved (struct btf_verifier_env*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int env_stack_push (struct btf_verifier_env*,struct btf_type const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  env_type_is_resolve_sink (struct btf_verifier_env*,struct btf_type const*) ; 
 scalar_t__ env_type_is_resolved (struct btf_verifier_env*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btf_modifier_resolve(struct btf_verifier_env *env,
				const struct resolve_vertex *v)
{
	const struct btf_type *t = v->t;
	const struct btf_type *next_type;
	u32 next_type_id = t->type;
	struct btf *btf = env->btf;

	next_type = btf_type_by_id(btf, next_type_id);
	if (!next_type || btf_type_is_resolve_source_only(next_type)) {
		btf_verifier_log_type(env, v->t, "Invalid type_id");
		return -EINVAL;
	}

	if (!env_type_is_resolve_sink(env, next_type) &&
	    !env_type_is_resolved(env, next_type_id))
		return env_stack_push(env, next_type, next_type_id);

	/* Figure out the resolved next_type_id with size.
	 * They will be stored in the current modifier's
	 * resolved_ids and resolved_sizes such that it can
	 * save us a few type-following when we use it later (e.g. in
	 * pretty print).
	 */
	if (!btf_type_id_size(btf, &next_type_id, NULL)) {
		if (env_type_is_resolved(env, next_type_id))
			next_type = btf_type_id_resolve(btf, &next_type_id);

		/* "typedef void new_void", "const void"...etc */
		if (!btf_type_is_void(next_type) &&
		    !btf_type_is_fwd(next_type) &&
		    !btf_type_is_func_proto(next_type)) {
			btf_verifier_log_type(env, v->t, "Invalid type_id");
			return -EINVAL;
		}
	}

	env_stack_pop_resolved(env, next_type_id, 0);

	return 0;
}