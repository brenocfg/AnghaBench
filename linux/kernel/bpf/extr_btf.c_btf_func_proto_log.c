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
typedef  int u16 ;
struct btf_verifier_env {int /*<<< orphan*/  btf; } ;
struct btf_type {int /*<<< orphan*/  type; } ;
struct btf_param {int /*<<< orphan*/  name_off; scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  __btf_name_by_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btf_type_vlen (struct btf_type const*) ; 
 int /*<<< orphan*/  btf_verifier_log (struct btf_verifier_env*,char*,...) ; 

__attribute__((used)) static void btf_func_proto_log(struct btf_verifier_env *env,
			       const struct btf_type *t)
{
	const struct btf_param *args = (const struct btf_param *)(t + 1);
	u16 nr_args = btf_type_vlen(t), i;

	btf_verifier_log(env, "return=%u args=(", t->type);
	if (!nr_args) {
		btf_verifier_log(env, "void");
		goto done;
	}

	if (nr_args == 1 && !args[0].type) {
		/* Only one vararg */
		btf_verifier_log(env, "vararg");
		goto done;
	}

	btf_verifier_log(env, "%u %s", args[0].type,
			 __btf_name_by_offset(env->btf,
					      args[0].name_off));
	for (i = 1; i < nr_args - 1; i++)
		btf_verifier_log(env, ", %u %s", args[i].type,
				 __btf_name_by_offset(env->btf,
						      args[i].name_off));

	if (nr_args > 1) {
		const struct btf_param *last_arg = &args[nr_args - 1];

		if (last_arg->type)
			btf_verifier_log(env, ", %u %s", last_arg->type,
					 __btf_name_by_offset(env->btf,
							      last_arg->name_off));
		else
			btf_verifier_log(env, ", vararg");
	}

done:
	btf_verifier_log(env, ")");
}