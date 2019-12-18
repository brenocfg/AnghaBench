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
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 unsigned long PHYS_PFN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageHighMem (int /*<<< orphan*/ ) ; 
 void* __va (int /*<<< orphan*/ ) ; 
 scalar_t__ arch_memremap_can_ram_remap (int /*<<< orphan*/ ,size_t,unsigned long) ; 
 int /*<<< orphan*/  pfn_to_page (unsigned long) ; 
 scalar_t__ pfn_valid (unsigned long) ; 

__attribute__((used)) static void *try_ram_remap(resource_size_t offset, size_t size,
			   unsigned long flags)
{
	unsigned long pfn = PHYS_PFN(offset);

	/* In the simple case just return the existing linear address */
	if (pfn_valid(pfn) && !PageHighMem(pfn_to_page(pfn)) &&
	    arch_memremap_can_ram_remap(offset, size, flags))
		return __va(offset);

	return NULL; /* fallback to arch_memremap_wb */
}