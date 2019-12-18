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
struct btf_type {int dummy; } ;
struct btf_member {int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTF_MEMBER_BITFIELD_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ btf_type_kflag (struct btf_type const*) ; 

__attribute__((used)) static u32 btf_member_bitfield_size(const struct btf_type *struct_type,
				    const struct btf_member *member)
{
	return btf_type_kflag(struct_type) ? BTF_MEMBER_BITFIELD_SIZE(member->offset)
					   : 0;
}