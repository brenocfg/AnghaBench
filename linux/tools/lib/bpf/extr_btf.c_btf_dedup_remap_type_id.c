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
struct btf_dedup {size_t* hypot_map; } ;
typedef  size_t __u32 ;

/* Variables and functions */
 size_t BTF_MAX_NR_TYPES ; 
 int EINVAL ; 
 size_t resolve_type_id (struct btf_dedup*,size_t) ; 

__attribute__((used)) static int btf_dedup_remap_type_id(struct btf_dedup *d, __u32 type_id)
{
	__u32 resolved_type_id, new_type_id;

	resolved_type_id = resolve_type_id(d, type_id);
	new_type_id = d->hypot_map[resolved_type_id];
	if (new_type_id > BTF_MAX_NR_TYPES)
		return -EINVAL;
	return new_type_id;
}