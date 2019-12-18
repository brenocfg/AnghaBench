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
struct btf_verifier_env {int /*<<< orphan*/  btf; } ;
struct btf_type {int /*<<< orphan*/  name_off; scalar_t__ type; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  btf_name_valid_identifier (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ btf_type_vlen (struct btf_type const*) ; 
 int /*<<< orphan*/  btf_verifier_log_type (struct btf_verifier_env*,struct btf_type const*,char*) ; 

__attribute__((used)) static s32 btf_fwd_check_meta(struct btf_verifier_env *env,
			      const struct btf_type *t,
			      u32 meta_left)
{
	if (btf_type_vlen(t)) {
		btf_verifier_log_type(env, t, "vlen != 0");
		return -EINVAL;
	}

	if (t->type) {
		btf_verifier_log_type(env, t, "type != 0");
		return -EINVAL;
	}

	/* fwd type must have a valid name */
	if (!t->name_off ||
	    !btf_name_valid_identifier(env->btf, t->name_off)) {
		btf_verifier_log_type(env, t, "Invalid name");
		return -EINVAL;
	}

	btf_verifier_log_type(env, t, NULL);

	return 0;
}