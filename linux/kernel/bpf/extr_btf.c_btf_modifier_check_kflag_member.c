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
typedef  int /*<<< orphan*/  u32 ;
struct btf_verifier_env {struct btf* btf; } ;
struct btf_type {int dummy; } ;
struct btf_member {int /*<<< orphan*/  type; } ;
struct btf {int dummy; } ;
struct TYPE_2__ {int (* check_kflag_member ) (struct btf_verifier_env*,struct btf_type const*,struct btf_member*,struct btf_type const*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 struct btf_type* btf_type_id_size (struct btf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* btf_type_ops (struct btf_type const*) ; 
 int /*<<< orphan*/  btf_verifier_log_member (struct btf_verifier_env*,struct btf_type const*,struct btf_member const*,char*) ; 
 int stub1 (struct btf_verifier_env*,struct btf_type const*,struct btf_member*,struct btf_type const*) ; 

__attribute__((used)) static int btf_modifier_check_kflag_member(struct btf_verifier_env *env,
					   const struct btf_type *struct_type,
					   const struct btf_member *member,
					   const struct btf_type *member_type)
{
	const struct btf_type *resolved_type;
	u32 resolved_type_id = member->type;
	struct btf_member resolved_member;
	struct btf *btf = env->btf;

	resolved_type = btf_type_id_size(btf, &resolved_type_id, NULL);
	if (!resolved_type) {
		btf_verifier_log_member(env, struct_type, member,
					"Invalid member");
		return -EINVAL;
	}

	resolved_member = *member;
	resolved_member.type = resolved_type_id;

	return btf_type_ops(resolved_type)->check_kflag_member(env, struct_type,
							       &resolved_member,
							       resolved_type);
}