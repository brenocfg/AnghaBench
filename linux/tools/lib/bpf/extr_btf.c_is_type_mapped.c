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
typedef  size_t uint32_t ;
struct btf_dedup {scalar_t__* map; } ;

/* Variables and functions */
 scalar_t__ BTF_MAX_NR_TYPES ; 

__attribute__((used)) static inline bool is_type_mapped(struct btf_dedup *d, uint32_t type_id)
{
	return d->map[type_id] <= BTF_MAX_NR_TYPES;
}