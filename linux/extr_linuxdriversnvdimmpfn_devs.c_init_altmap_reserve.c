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
 unsigned long PFN_SECTION_ALIGN_DOWN (unsigned long) ; 
 unsigned long PFN_UP (int /*<<< orphan*/ ) ; 
 unsigned long PHYS_PFN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_8K ; 

__attribute__((used)) static unsigned long init_altmap_reserve(resource_size_t base)
{
	unsigned long reserve = PFN_UP(SZ_8K);
	unsigned long base_pfn = PHYS_PFN(base);

	reserve += base_pfn - PFN_SECTION_ALIGN_DOWN(base_pfn);
	return reserve;
}