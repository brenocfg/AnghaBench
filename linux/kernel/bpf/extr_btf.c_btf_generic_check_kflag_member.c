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
struct btf_verifier_env {int dummy; } ;
struct btf_type {int dummy; } ;
struct btf_member {int /*<<< orphan*/  offset; } ;
struct TYPE_2__ {int (* check_member ) (struct btf_verifier_env*,struct btf_type const*,struct btf_member const*,struct btf_type const*) ;} ;

/* Variables and functions */
 scalar_t__ BTF_MEMBER_BITFIELD_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 TYPE_1__* btf_type_ops (struct btf_type const*) ; 
 int /*<<< orphan*/  btf_verifier_log_member (struct btf_verifier_env*,struct btf_type const*,struct btf_member const*,char*) ; 
 int stub1 (struct btf_verifier_env*,struct btf_type const*,struct btf_member const*,struct btf_type const*) ; 

__attribute__((used)) static int btf_generic_check_kflag_member(struct btf_verifier_env *env,
					  const struct btf_type *struct_type,
					  const struct btf_member *member,
					  const struct btf_type *member_type)
{
	if (BTF_MEMBER_BITFIELD_SIZE(member->offset)) {
		btf_verifier_log_member(env, struct_type, member,
					"Invalid member bitfield_size");
		return -EINVAL;
	}

	/* bitfield size is 0, so member->offset represents bit offset only.
	 * It is safe to call non kflag check_member variants.
	 */
	return btf_type_ops(member_type)->check_member(env, struct_type,
						       member,
						       member_type);
}