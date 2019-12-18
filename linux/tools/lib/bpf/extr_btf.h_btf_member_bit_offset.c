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
struct btf_type {int dummy; } ;
struct btf_member {int offset; } ;
typedef  int __u32 ;

/* Variables and functions */
 int BTF_MEMBER_BIT_OFFSET (int) ; 
 int btf_kflag (struct btf_type const*) ; 
 struct btf_member* btf_members (struct btf_type const*) ; 

__attribute__((used)) static inline __u32 btf_member_bit_offset(const struct btf_type *t,
					  __u32 member_idx)
{
	const struct btf_member *m = btf_members(t) + member_idx;
	bool kflag = btf_kflag(t);

	return kflag ? BTF_MEMBER_BIT_OFFSET(m->offset) : m->offset;
}