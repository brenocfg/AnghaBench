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
struct vmem_altmap {unsigned long alloc; } ;

/* Variables and functions */

void vmem_altmap_free(struct vmem_altmap *altmap, unsigned long nr_pfns)
{
	altmap->alloc -= nr_pfns;
}