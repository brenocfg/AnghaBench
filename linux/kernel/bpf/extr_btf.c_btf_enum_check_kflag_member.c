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
struct btf_verifier_env {int dummy; } ;
struct btf_type {scalar_t__ size; } ;
struct btf_member {int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int BITS_PER_BYTE ; 
 scalar_t__ BITS_PER_BYTE_MASKED (scalar_t__) ; 
 scalar_t__ BITS_ROUNDUP_BYTES (scalar_t__) ; 
 scalar_t__ BTF_MEMBER_BITFIELD_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ BTF_MEMBER_BIT_OFFSET (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  btf_verifier_log_member (struct btf_verifier_env*,struct btf_type const*,struct btf_member const*,char*) ; 

__attribute__((used)) static int btf_enum_check_kflag_member(struct btf_verifier_env *env,
				       const struct btf_type *struct_type,
				       const struct btf_member *member,
				       const struct btf_type *member_type)
{
	u32 struct_bits_off, nr_bits, bytes_end, struct_size;
	u32 int_bitsize = sizeof(int) * BITS_PER_BYTE;

	struct_bits_off = BTF_MEMBER_BIT_OFFSET(member->offset);
	nr_bits = BTF_MEMBER_BITFIELD_SIZE(member->offset);
	if (!nr_bits) {
		if (BITS_PER_BYTE_MASKED(struct_bits_off)) {
			btf_verifier_log_member(env, struct_type, member,
						"Member is not byte aligned");
			return -EINVAL;
		}

		nr_bits = int_bitsize;
	} else if (nr_bits > int_bitsize) {
		btf_verifier_log_member(env, struct_type, member,
					"Invalid member bitfield_size");
		return -EINVAL;
	}

	struct_size = struct_type->size;
	bytes_end = BITS_ROUNDUP_BYTES(struct_bits_off + nr_bits);
	if (struct_size < bytes_end) {
		btf_verifier_log_member(env, struct_type, member,
					"Member exceeds struct_size");
		return -EINVAL;
	}

	return 0;
}