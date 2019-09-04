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
struct vm_area_struct {int vm_flags; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_MLOCK ; 
 int /*<<< orphan*/  PageLRU (struct page*) ; 
 int /*<<< orphan*/  SetPageActive (struct page*) ; 
 int /*<<< orphan*/  TestSetPageMlocked (struct page*) ; 
 int /*<<< orphan*/  UNEVICTABLE_PGMLOCKED ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int /*<<< orphan*/ ,struct page*) ; 
 int VM_LOCKED ; 
 int VM_SPECIAL ; 
 int /*<<< orphan*/  __mod_zone_page_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count_vm_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpage_nr_pages (struct page*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  lru_cache_add (struct page*) ; 
 int /*<<< orphan*/  page_zone (struct page*) ; 

void lru_cache_add_active_or_unevictable(struct page *page,
					 struct vm_area_struct *vma)
{
	VM_BUG_ON_PAGE(PageLRU(page), page);

	if (likely((vma->vm_flags & (VM_LOCKED | VM_SPECIAL)) != VM_LOCKED))
		SetPageActive(page);
	else if (!TestSetPageMlocked(page)) {
		/*
		 * We use the irq-unsafe __mod_zone_page_stat because this
		 * counter is not modified from interrupt context, and the pte
		 * lock is held(spinlock), which implies preemption disabled.
		 */
		__mod_zone_page_state(page_zone(page), NR_MLOCK,
				    hpage_nr_pages(page));
		count_vm_event(UNEVICTABLE_PGMLOCKED);
	}
	lru_cache_add(page);
}