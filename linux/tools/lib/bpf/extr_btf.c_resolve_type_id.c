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
struct btf_dedup {size_t* map; } ;
typedef  size_t __u32 ;

/* Variables and functions */
 scalar_t__ is_type_mapped (struct btf_dedup*,size_t) ; 

__attribute__((used)) static inline __u32 resolve_type_id(struct btf_dedup *d, __u32 type_id)
{
	while (is_type_mapped(d, type_id) && d->map[type_id] != type_id)
		type_id = d->map[type_id];
	return type_id;
}