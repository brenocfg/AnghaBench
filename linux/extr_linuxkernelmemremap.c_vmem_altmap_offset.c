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
struct vmem_altmap {unsigned long reserve; unsigned long free; } ;

/* Variables and functions */

unsigned long vmem_altmap_offset(struct vmem_altmap *altmap)
{
	/* number of pfns from base where pfn_to_page() is valid */
	return altmap->reserve + altmap->free;
}