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
typedef  void* u32 ;
struct resolve_vertex {int /*<<< orphan*/  t; void* type_id; } ;
struct btf_verifier_env {void* log_type_id; int /*<<< orphan*/  resolve_mode; } ;
struct btf_type {int dummy; } ;
struct TYPE_2__ {int (* resolve ) (struct btf_verifier_env*,struct resolve_vertex const*) ;} ;

/* Variables and functions */
 int E2BIG ; 
 int EEXIST ; 
 int EINVAL ; 
 int /*<<< orphan*/  MAX_RESOLVE_DEPTH ; 
 int /*<<< orphan*/  RESOLVE_TBD ; 
 int /*<<< orphan*/  btf_resolve_valid (struct btf_verifier_env*,struct btf_type const*,void*) ; 
 TYPE_1__* btf_type_ops (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btf_verifier_log_type (struct btf_verifier_env*,struct btf_type const*,char*,...) ; 
 struct resolve_vertex* env_stack_peak (struct btf_verifier_env*) ; 
 int /*<<< orphan*/  env_stack_push (struct btf_verifier_env*,struct btf_type const*,void*) ; 
 int stub1 (struct btf_verifier_env*,struct resolve_vertex const*) ; 

__attribute__((used)) static int btf_resolve(struct btf_verifier_env *env,
		       const struct btf_type *t, u32 type_id)
{
	u32 save_log_type_id = env->log_type_id;
	const struct resolve_vertex *v;
	int err = 0;

	env->resolve_mode = RESOLVE_TBD;
	env_stack_push(env, t, type_id);
	while (!err && (v = env_stack_peak(env))) {
		env->log_type_id = v->type_id;
		err = btf_type_ops(v->t)->resolve(env, v);
	}

	env->log_type_id = type_id;
	if (err == -E2BIG) {
		btf_verifier_log_type(env, t,
				      "Exceeded max resolving depth:%u",
				      MAX_RESOLVE_DEPTH);
	} else if (err == -EEXIST) {
		btf_verifier_log_type(env, t, "Loop detected");
	}

	/* Final sanity check */
	if (!err && !btf_resolve_valid(env, t, type_id)) {
		btf_verifier_log_type(env, t, "Invalid resolve state");
		err = -EINVAL;
	}

	env->log_type_id = save_log_type_id;
	return err;
}