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
struct vgic_register_region {int dummy; } ;
typedef  int /*<<< orphan*/  regions ;

/* Variables and functions */
 struct vgic_register_region const* bsearch (void*,struct vgic_register_region const*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  match_region ; 

const struct vgic_register_region *
vgic_find_mmio_region(const struct vgic_register_region *regions,
		      int nr_regions, unsigned int offset)
{
	return bsearch((void *)(uintptr_t)offset, regions, nr_regions,
		       sizeof(regions[0]), match_region);
}