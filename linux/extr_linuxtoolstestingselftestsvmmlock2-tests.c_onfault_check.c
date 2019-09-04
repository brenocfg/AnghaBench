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
 int PRESENT_BIT ; 
 int UNEVICTABLE_BIT ; 
 int get_kpageflags (int) ; 
 int get_pageflags (unsigned long) ; 
 unsigned long getpagesize () ; 
 int /*<<< orphan*/  is_vma_lock_on_fault (unsigned long) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int onfault_check(char *map)
{
	unsigned long page_size = getpagesize();
	uint64_t page1_flags, page2_flags;

	page1_flags = get_pageflags((unsigned long)map);
	page2_flags = get_pageflags((unsigned long)map + page_size);

	/* Neither page should be present */
	if ((page1_flags & PRESENT_BIT) || (page2_flags & PRESENT_BIT)) {
		printf("Pages were made present by MLOCK_ONFAULT\n");
		return 1;
	}

	*map = 'a';
	page1_flags = get_pageflags((unsigned long)map);
	page2_flags = get_pageflags((unsigned long)map + page_size);

	/* Only page 1 should be present */
	if ((page1_flags & PRESENT_BIT) == 0) {
		printf("Page 1 is not present after fault\n");
		return 1;
	} else if (page2_flags & PRESENT_BIT) {
		printf("Page 2 was made present\n");
		return 1;
	}

	page1_flags = get_kpageflags(page1_flags & PFN_MASK);

	/* Page 1 should be unevictable */
	if ((page1_flags & UNEVICTABLE_BIT) == 0) {
		printf("Failed to make faulted page unevictable\n");
		return 1;
	}

	if (!is_vma_lock_on_fault((unsigned long)map)) {
		printf("VMA is not marked for lock on fault\n");
		return 1;
	}

	if (!is_vma_lock_on_fault((unsigned long)map + page_size)) {
		printf("VMA is not marked for lock on fault\n");
		return 1;
	}

	return 0;
}