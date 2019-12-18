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
typedef  int u16 ;
struct btf_verifier_env {struct btf* btf; } ;
struct btf_type {scalar_t__ type; } ;
struct btf_param {scalar_t__ name_off; scalar_t__ type; } ;
struct btf {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  btf_name_offset_valid (struct btf const*,scalar_t__) ; 
 int /*<<< orphan*/  btf_name_valid_identifier (struct btf const*,scalar_t__) ; 
 int btf_resolve (struct btf_verifier_env*,struct btf_type const*,scalar_t__) ; 
 struct btf_type* btf_type_by_id (struct btf const*,scalar_t__) ; 
 int /*<<< orphan*/  btf_type_id_size (struct btf const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ btf_type_needs_resolve (struct btf_type const*) ; 
 int btf_type_vlen (struct btf_type const*) ; 
 int /*<<< orphan*/  btf_verifier_log_type (struct btf_verifier_env*,struct btf_type const*,char*,...) ; 
 int /*<<< orphan*/  env_type_is_resolved (struct btf_verifier_env*,scalar_t__) ; 

__attribute__((used)) static int btf_func_proto_check(struct btf_verifier_env *env,
				const struct btf_type *t)
{
	const struct btf_type *ret_type;
	const struct btf_param *args;
	const struct btf *btf;
	u16 nr_args, i;
	int err;

	btf = env->btf;
	args = (const struct btf_param *)(t + 1);
	nr_args = btf_type_vlen(t);

	/* Check func return type which could be "void" (t->type == 0) */
	if (t->type) {
		u32 ret_type_id = t->type;

		ret_type = btf_type_by_id(btf, ret_type_id);
		if (!ret_type) {
			btf_verifier_log_type(env, t, "Invalid return type");
			return -EINVAL;
		}

		if (btf_type_needs_resolve(ret_type) &&
		    !env_type_is_resolved(env, ret_type_id)) {
			err = btf_resolve(env, ret_type, ret_type_id);
			if (err)
				return err;
		}

		/* Ensure the return type is a type that has a size */
		if (!btf_type_id_size(btf, &ret_type_id, NULL)) {
			btf_verifier_log_type(env, t, "Invalid return type");
			return -EINVAL;
		}
	}

	if (!nr_args)
		return 0;

	/* Last func arg type_id could be 0 if it is a vararg */
	if (!args[nr_args - 1].type) {
		if (args[nr_args - 1].name_off) {
			btf_verifier_log_type(env, t, "Invalid arg#%u",
					      nr_args);
			return -EINVAL;
		}
		nr_args--;
	}

	err = 0;
	for (i = 0; i < nr_args; i++) {
		const struct btf_type *arg_type;
		u32 arg_type_id;

		arg_type_id = args[i].type;
		arg_type = btf_type_by_id(btf, arg_type_id);
		if (!arg_type) {
			btf_verifier_log_type(env, t, "Invalid arg#%u", i + 1);
			err = -EINVAL;
			break;
		}

		if (args[i].name_off &&
		    (!btf_name_offset_valid(btf, args[i].name_off) ||
		     !btf_name_valid_identifier(btf, args[i].name_off))) {
			btf_verifier_log_type(env, t,
					      "Invalid arg#%u", i + 1);
			err = -EINVAL;
			break;
		}

		if (btf_type_needs_resolve(arg_type) &&
		    !env_type_is_resolved(env, arg_type_id)) {
			err = btf_resolve(env, arg_type, arg_type_id);
			if (err)
				break;
		}

		if (!btf_type_id_size(btf, &arg_type_id, NULL)) {
			btf_verifier_log_type(env, t, "Invalid arg#%u", i + 1);
			err = -EINVAL;
			break;
		}
	}

	return err;
}