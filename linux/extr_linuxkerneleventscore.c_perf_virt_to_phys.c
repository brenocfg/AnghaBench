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
typedef  int u64 ;
struct page {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * mm; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int TASK_SIZE ; 
 int VMALLOC_END ; 
 int VMALLOC_START ; 
 int __get_user_pages_fast (int,int,int /*<<< orphan*/ ,struct page**) ; 
 TYPE_1__* current ; 
 int page_to_phys (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 scalar_t__ virt_addr_valid (void*) ; 
 scalar_t__ virt_to_phys (void*) ; 

__attribute__((used)) static u64 perf_virt_to_phys(u64 virt)
{
	u64 phys_addr = 0;
	struct page *p = NULL;

	if (!virt)
		return 0;

	if (virt >= TASK_SIZE) {
		/* If it's vmalloc()d memory, leave phys_addr as 0 */
		if (virt_addr_valid((void *)(uintptr_t)virt) &&
		    !(virt >= VMALLOC_START && virt < VMALLOC_END))
			phys_addr = (u64)virt_to_phys((void *)(uintptr_t)virt);
	} else {
		/*
		 * Walking the pages tables for user address.
		 * Interrupts are disabled, so it prevents any tear down
		 * of the page tables.
		 * Try IRQ-safe __get_user_pages_fast first.
		 * If failed, leave phys_addr as 0.
		 */
		if ((current->mm != NULL) &&
		    (__get_user_pages_fast(virt, 1, 0, &p) == 1))
			phys_addr = page_to_phys(p) + virt % PAGE_SIZE;

		if (p)
			put_page(p);
	}

	return phys_addr;
}