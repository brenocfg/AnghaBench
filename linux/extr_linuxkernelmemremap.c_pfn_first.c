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
struct vmem_altmap {int dummy; } ;
struct resource {unsigned long start; } ;
struct dev_pagemap {scalar_t__ altmap_valid; struct vmem_altmap altmap; struct resource res; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 scalar_t__ vmem_altmap_offset (struct vmem_altmap*) ; 

__attribute__((used)) static unsigned long pfn_first(struct dev_pagemap *pgmap)
{
	const struct resource *res = &pgmap->res;
	struct vmem_altmap *altmap = &pgmap->altmap;
	unsigned long pfn;

	pfn = res->start >> PAGE_SHIFT;
	if (pgmap->altmap_valid)
		pfn += vmem_altmap_offset(altmap);
	return pfn;
}