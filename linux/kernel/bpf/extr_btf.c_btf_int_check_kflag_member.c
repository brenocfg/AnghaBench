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
 scalar_t__ BITS_PER_BYTE_MASKED (scalar_t__) ; 
 scalar_t__ BITS_PER_U128 ; 
 scalar_t__ BITS_ROUNDDOWN_BYTES (scalar_t__) ; 
 scalar_t__ BITS_ROUNDUP_BYTES (scalar_t__) ; 
 scalar_t__ BTF_INT_BITS (scalar_t__) ; 
 scalar_t__ BTF_MEMBER_BITFIELD_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ BTF_MEMBER_BIT_OFFSET (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ btf_type_int (struct btf_type const*) ; 
 int /*<<< orphan*/  btf_type_int_is_regular (struct btf_type const*) ; 
 int /*<<< orphan*/  btf_verifier_log_member (struct btf_verifier_env*,struct btf_type const*,struct btf_member const*,char*) ; 

__attribute__((used)) static int btf_int_check_kflag_member(struct btf_verifier_env *env,
				      const struct btf_type *struct_type,
				      const struct btf_member *member,
				      const struct btf_type *member_type)
{
	u32 struct_bits_off, nr_bits, nr_int_data_bits, bytes_offset;
	u32 int_data = btf_type_int(member_type);
	u32 struct_size = struct_type->size;
	u32 nr_copy_bits;

	/* a regular int type is required for the kflag int member */
	if (!btf_type_int_is_regular(member_type)) {
		btf_verifier_log_member(env, struct_type, member,
					"Invalid member base type");
		return -EINVAL;
	}

	/* check sanity of bitfield size */
	nr_bits = BTF_MEMBER_BITFIELD_SIZE(member->offset);
	struct_bits_off = BTF_MEMBER_BIT_OFFSET(member->offset);
	nr_int_data_bits = BTF_INT_BITS(int_data);
	if (!nr_bits) {
		/* Not a bitfield member, member offset must be at byte
		 * boundary.
		 */
		if (BITS_PER_BYTE_MASKED(struct_bits_off)) {
			btf_verifier_log_member(env, struct_type, member,
						"Invalid member offset");
			return -EINVAL;
		}

		nr_bits = nr_int_data_bits;
	} else if (nr_bits > nr_int_data_bits) {
		btf_verifier_log_member(env, struct_type, member,
					"Invalid member bitfield_size");
		return -EINVAL;
	}

	bytes_offset = BITS_ROUNDDOWN_BYTES(struct_bits_off);
	nr_copy_bits = nr_bits + BITS_PER_BYTE_MASKED(struct_bits_off);
	if (nr_copy_bits > BITS_PER_U128) {
		btf_verifier_log_member(env, struct_type, member,
					"nr_copy_bits exceeds 128");
		return -EINVAL;
	}

	if (struct_size < bytes_offset ||
	    struct_size - bytes_offset < BITS_ROUNDUP_BYTES(nr_copy_bits)) {
		btf_verifier_log_member(env, struct_type, member,
					"Member exceeds struct_size");
		return -EINVAL;
	}

	return 0;
}