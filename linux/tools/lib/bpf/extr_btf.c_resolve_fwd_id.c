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
typedef  size_t uint32_t ;
struct btf_dedup {size_t* map; TYPE_1__* btf; } ;
typedef  size_t __u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * types; } ;

/* Variables and functions */
 int /*<<< orphan*/  btf_is_fwd (int /*<<< orphan*/ ) ; 
 scalar_t__ is_type_mapped (struct btf_dedup*,size_t) ; 

__attribute__((used)) static uint32_t resolve_fwd_id(struct btf_dedup *d, uint32_t type_id)
{
	__u32 orig_type_id = type_id;

	if (!btf_is_fwd(d->btf->types[type_id]))
		return type_id;

	while (is_type_mapped(d, type_id) && d->map[type_id] != type_id)
		type_id = d->map[type_id];

	if (!btf_is_fwd(d->btf->types[type_id]))
		return type_id;

	return orig_type_id;
}