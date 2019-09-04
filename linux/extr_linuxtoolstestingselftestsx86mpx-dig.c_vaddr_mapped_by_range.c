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
struct vaddr_range {int dummy; } ;

/* Variables and functions */
 size_t last_range ; 
 int nr_ranges_populated ; 
 struct vaddr_range* ranges ; 
 scalar_t__ vaddr_in_range (unsigned long,struct vaddr_range*) ; 

__attribute__((used)) static inline int vaddr_mapped_by_range(unsigned long vaddr)
{
	int i;

	if (last_range > 0 && vaddr_in_range(vaddr, &ranges[last_range]))
		return 1;

	for (i = 0; i < nr_ranges_populated; i++) {
		struct vaddr_range *r = &ranges[i];

		if (vaddr_in_range(vaddr, r))
			continue;
		last_range = i;
		return 1;
	}
	return 0;
}