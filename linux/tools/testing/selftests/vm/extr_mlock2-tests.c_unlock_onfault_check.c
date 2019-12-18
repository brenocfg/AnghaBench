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
typedef  int uint64_t ;

/* Variables and functions */
 int PFN_MASK ; 
 int UNEVICTABLE_BIT ; 
 int get_kpageflags (int) ; 
 int get_pageflags (unsigned long) ; 
 unsigned long getpagesize () ; 
 scalar_t__ is_vma_lock_on_fault (unsigned long) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int unlock_onfault_check(char *map)
{
	unsigned long page_size = getpagesize();
	uint64_t page1_flags;

	page1_flags = get_pageflags((unsigned long)map);
	page1_flags = get_kpageflags(page1_flags & PFN_MASK);

	if (page1_flags & UNEVICTABLE_BIT) {
		printf("Page 1 is still marked unevictable after unlock\n");
		return 1;
	}

	if (is_vma_lock_on_fault((unsigned long)map) ||
	    is_vma_lock_on_fault((unsigned long)map + page_size)) {
		printf("VMA is still lock on fault after unlock\n");
		return 1;
	}

	return 0;
}