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
 int PAGE_SIZE ; 
 int dax_entry_size (void*) ; 
 unsigned long dax_to_pfn (void*) ; 

__attribute__((used)) static unsigned long dax_end_pfn(void *entry)
{
	return dax_to_pfn(entry) + dax_entry_size(entry) / PAGE_SIZE;
}