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
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  flush_dcache_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  offset_in_page (void*) ; 
 size_t round_up (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  virt_to_page (void*) ; 

__attribute__((used)) static inline void tcmu_flush_dcache_range(void *vaddr, size_t size)
{
	unsigned long offset = offset_in_page(vaddr);
	void *start = vaddr - offset;

	size = round_up(size+offset, PAGE_SIZE);

	while (size) {
		flush_dcache_page(virt_to_page(start));
		start += PAGE_SIZE;
		size -= PAGE_SIZE;
	}
}