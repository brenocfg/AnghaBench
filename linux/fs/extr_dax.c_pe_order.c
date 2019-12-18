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
typedef  enum page_entry_size { ____Placeholder_page_entry_size } page_entry_size ;

/* Variables and functions */
 unsigned int PAGE_SHIFT ; 
 int PE_SIZE_PMD ; 
 int PE_SIZE_PTE ; 
 int PE_SIZE_PUD ; 
 unsigned int PMD_SHIFT ; 
 unsigned int PUD_SHIFT ; 

__attribute__((used)) static inline unsigned int pe_order(enum page_entry_size pe_size)
{
	if (pe_size == PE_SIZE_PTE)
		return PAGE_SHIFT - PAGE_SHIFT;
	if (pe_size == PE_SIZE_PMD)
		return PMD_SHIFT - PAGE_SHIFT;
	if (pe_size == PE_SIZE_PUD)
		return PUD_SHIFT - PAGE_SHIFT;
	return ~0;
}