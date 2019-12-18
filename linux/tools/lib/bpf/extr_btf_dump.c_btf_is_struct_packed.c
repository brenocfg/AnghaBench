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
struct btf_type {int size; } ;
struct btf_member {int offset; int /*<<< orphan*/  type; } ;
struct btf {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  int __u16 ;

/* Variables and functions */
 int btf_align_of (struct btf const*,int /*<<< orphan*/ ) ; 
 int btf_member_bitfield_size (struct btf_type const*,int) ; 
 struct btf_member* btf_members (struct btf_type const*) ; 
 int btf_vlen (struct btf_type const*) ; 

__attribute__((used)) static bool btf_is_struct_packed(const struct btf *btf, __u32 id,
				 const struct btf_type *t)
{
	const struct btf_member *m;
	int align, i, bit_sz;
	__u16 vlen;

	align = btf_align_of(btf, id);
	/* size of a non-packed struct has to be a multiple of its alignment*/
	if (t->size % align)
		return true;

	m = btf_members(t);
	vlen = btf_vlen(t);
	/* all non-bitfield fields have to be naturally aligned */
	for (i = 0; i < vlen; i++, m++) {
		align = btf_align_of(btf, m->type);
		bit_sz = btf_member_bitfield_size(t, i);
		if (bit_sz == 0 && m->offset % (8 * align) != 0)
			return true;
	}

	/*
	 * if original struct was marked as packed, but its layout is
	 * naturally aligned, we'll detect that it's not packed
	 */
	return false;
}