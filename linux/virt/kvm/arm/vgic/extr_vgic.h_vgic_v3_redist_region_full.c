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
struct vgic_redist_region {scalar_t__ count; scalar_t__ free_index; } ;

/* Variables and functions */

__attribute__((used)) static inline bool
vgic_v3_redist_region_full(struct vgic_redist_region *region)
{
	if (!region->count)
		return false;

	return (region->free_index >= region->count);
}