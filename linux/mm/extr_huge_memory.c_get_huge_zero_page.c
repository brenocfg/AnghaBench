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
struct page {int dummy; } ;

/* Variables and functions */
 int GFP_TRANSHUGE ; 
 int /*<<< orphan*/  HPAGE_PMD_ORDER ; 
 struct page* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THP_ZERO_PAGE_ALLOC ; 
 int /*<<< orphan*/  THP_ZERO_PAGE_ALLOC_FAILED ; 
 int __GFP_MOVABLE ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  __free_pages (struct page*,int /*<<< orphan*/ ) ; 
 struct page* alloc_pages (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct page*) ; 
 int /*<<< orphan*/  compound_order (struct page*) ; 
 int /*<<< orphan*/  count_vm_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  huge_zero_page ; 
 int /*<<< orphan*/  huge_zero_refcount ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

__attribute__((used)) static struct page *get_huge_zero_page(void)
{
	struct page *zero_page;
retry:
	if (likely(atomic_inc_not_zero(&huge_zero_refcount)))
		return READ_ONCE(huge_zero_page);

	zero_page = alloc_pages((GFP_TRANSHUGE | __GFP_ZERO) & ~__GFP_MOVABLE,
			HPAGE_PMD_ORDER);
	if (!zero_page) {
		count_vm_event(THP_ZERO_PAGE_ALLOC_FAILED);
		return NULL;
	}
	count_vm_event(THP_ZERO_PAGE_ALLOC);
	preempt_disable();
	if (cmpxchg(&huge_zero_page, NULL, zero_page)) {
		preempt_enable();
		__free_pages(zero_page, compound_order(zero_page));
		goto retry;
	}

	/* We take additional reference here. It will be put back by shrinker */
	atomic_set(&huge_zero_refcount, 2);
	preempt_enable();
	return READ_ONCE(huge_zero_page);
}