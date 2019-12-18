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
struct TYPE_2__ {int /*<<< orphan*/  start; } ;
struct dev_pagemap {TYPE_1__ res; } ;

/* Variables and functions */
 unsigned long PHYS_PFN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgmap_altmap (struct dev_pagemap*) ; 
 unsigned long vmem_altmap_offset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long pfn_first(struct dev_pagemap *pgmap)
{
	return PHYS_PFN(pgmap->res.start) +
		vmem_altmap_offset(pgmap_altmap(pgmap));
}