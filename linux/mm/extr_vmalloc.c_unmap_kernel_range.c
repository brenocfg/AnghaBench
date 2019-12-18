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

/* Variables and functions */
 int /*<<< orphan*/  flush_cache_vunmap (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  flush_tlb_kernel_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  vunmap_page_range (unsigned long,unsigned long) ; 

void unmap_kernel_range(unsigned long addr, unsigned long size)
{
	unsigned long end = addr + size;

	flush_cache_vunmap(addr, end);
	vunmap_page_range(addr, end);
	flush_tlb_kernel_range(addr, end);
}