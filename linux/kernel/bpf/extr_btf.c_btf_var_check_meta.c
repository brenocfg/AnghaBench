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
typedef  scalar_t__ u32 ;
struct btf_verifier_env {int /*<<< orphan*/  btf; } ;
struct btf_var {scalar_t__ linkage; } ;
struct btf_type {int /*<<< orphan*/  type; int /*<<< orphan*/  name_off; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BTF_TYPE_ID_VALID (int /*<<< orphan*/ ) ; 
 scalar_t__ BTF_VAR_GLOBAL_ALLOCATED ; 
 scalar_t__ BTF_VAR_STATIC ; 
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  __btf_name_valid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ btf_type_kflag (struct btf_type const*) ; 
 struct btf_var* btf_type_var (struct btf_type const*) ; 
 scalar_t__ btf_type_vlen (struct btf_type const*) ; 
 int /*<<< orphan*/  btf_verifier_log_basic (struct btf_verifier_env*,struct btf_type const*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  btf_verifier_log_type (struct btf_verifier_env*,struct btf_type const*,char*) ; 

__attribute__((used)) static s32 btf_var_check_meta(struct btf_verifier_env *env,
			      const struct btf_type *t,
			      u32 meta_left)
{
	const struct btf_var *var;
	u32 meta_needed = sizeof(*var);

	if (meta_left < meta_needed) {
		btf_verifier_log_basic(env, t,
				       "meta_left:%u meta_needed:%u",
				       meta_left, meta_needed);
		return -EINVAL;
	}

	if (btf_type_vlen(t)) {
		btf_verifier_log_type(env, t, "vlen != 0");
		return -EINVAL;
	}

	if (btf_type_kflag(t)) {
		btf_verifier_log_type(env, t, "Invalid btf_info kind_flag");
		return -EINVAL;
	}

	if (!t->name_off ||
	    !__btf_name_valid(env->btf, t->name_off, true)) {
		btf_verifier_log_type(env, t, "Invalid name");
		return -EINVAL;
	}

	/* A var cannot be in type void */
	if (!t->type || !BTF_TYPE_ID_VALID(t->type)) {
		btf_verifier_log_type(env, t, "Invalid type_id");
		return -EINVAL;
	}

	var = btf_type_var(t);
	if (var->linkage != BTF_VAR_STATIC &&
	    var->linkage != BTF_VAR_GLOBAL_ALLOCATED) {
		btf_verifier_log_type(env, t, "Linkage not supported");
		return -EINVAL;
	}

	btf_verifier_log_type(env, t, NULL);

	return meta_needed;
}