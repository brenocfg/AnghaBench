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
struct page {int dummy; } ;
struct address_space {TYPE_1__* a_ops; } ;
typedef  int /*<<< orphan*/  isolate_mode_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* isolate_page ) (struct page*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ PageIsolated (struct page*) ; 
 int /*<<< orphan*/  PageMovable (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (scalar_t__) ; 
 int /*<<< orphan*/  __PageMovable (struct page*) ; 
 int /*<<< orphan*/  __SetPageIsolated (struct page*) ; 
 int /*<<< orphan*/  get_page_unless_zero (struct page*) ; 
 struct address_space* page_mapping (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  stub1 (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trylock_page (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int isolate_movable_page(struct page *page, isolate_mode_t mode)
{
	struct address_space *mapping;

	/*
	 * Avoid burning cycles with pages that are yet under __free_pages(),
	 * or just got freed under us.
	 *
	 * In case we 'win' a race for a movable page being freed under us and
	 * raise its refcount preventing __free_pages() from doing its job
	 * the put_page() at the end of this block will take care of
	 * release this page, thus avoiding a nasty leakage.
	 */
	if (unlikely(!get_page_unless_zero(page)))
		goto out;

	/*
	 * Check PageMovable before holding a PG_lock because page's owner
	 * assumes anybody doesn't touch PG_lock of newly allocated page
	 * so unconditionally grabbing the lock ruins page's owner side.
	 */
	if (unlikely(!__PageMovable(page)))
		goto out_putpage;
	/*
	 * As movable pages are not isolated from LRU lists, concurrent
	 * compaction threads can race against page migration functions
	 * as well as race against the releasing a page.
	 *
	 * In order to avoid having an already isolated movable page
	 * being (wrongly) re-isolated while it is under migration,
	 * or to avoid attempting to isolate pages being released,
	 * lets be sure we have the page lock
	 * before proceeding with the movable page isolation steps.
	 */
	if (unlikely(!trylock_page(page)))
		goto out_putpage;

	if (!PageMovable(page) || PageIsolated(page))
		goto out_no_isolated;

	mapping = page_mapping(page);
	VM_BUG_ON_PAGE(!mapping, page);

	if (!mapping->a_ops->isolate_page(page, mode))
		goto out_no_isolated;

	/* Driver shouldn't use PG_isolated bit of page->flags */
	WARN_ON_ONCE(PageIsolated(page));
	__SetPageIsolated(page);
	unlock_page(page);

	return 0;

out_no_isolated:
	unlock_page(page);
out_putpage:
	put_page(page);
out:
	return -EBUSY;
}