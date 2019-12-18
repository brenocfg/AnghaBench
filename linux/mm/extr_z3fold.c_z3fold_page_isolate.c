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
struct z3fold_pool {int /*<<< orphan*/  lock; } ;
struct z3fold_header {scalar_t__ mapped_count; int /*<<< orphan*/  buddy; int /*<<< orphan*/  refcount; } ;
struct page {int /*<<< orphan*/  lru; int /*<<< orphan*/  private; } ;
typedef  int /*<<< orphan*/  isolate_mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  NEEDS_COMPACTING ; 
 int /*<<< orphan*/  PAGE_CLAIMED ; 
 int /*<<< orphan*/  PAGE_HEADLESS ; 
 int /*<<< orphan*/  PAGE_STALE ; 
 int PageIsolated (struct page*) ; 
 int /*<<< orphan*/  PageMovable (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct z3fold_header* page_address (struct page*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  z3fold_page_lock (struct z3fold_header*) ; 
 int /*<<< orphan*/  z3fold_page_unlock (struct z3fold_header*) ; 
 struct z3fold_pool* zhdr_to_pool (struct z3fold_header*) ; 

__attribute__((used)) static bool z3fold_page_isolate(struct page *page, isolate_mode_t mode)
{
	struct z3fold_header *zhdr;
	struct z3fold_pool *pool;

	VM_BUG_ON_PAGE(!PageMovable(page), page);
	VM_BUG_ON_PAGE(PageIsolated(page), page);

	if (test_bit(PAGE_HEADLESS, &page->private) ||
	    test_bit(PAGE_CLAIMED, &page->private))
		return false;

	zhdr = page_address(page);
	z3fold_page_lock(zhdr);
	if (test_bit(NEEDS_COMPACTING, &page->private) ||
	    test_bit(PAGE_STALE, &page->private))
		goto out;

	pool = zhdr_to_pool(zhdr);

	if (zhdr->mapped_count == 0) {
		kref_get(&zhdr->refcount);
		if (!list_empty(&zhdr->buddy))
			list_del_init(&zhdr->buddy);
		spin_lock(&pool->lock);
		if (!list_empty(&page->lru))
			list_del(&page->lru);
		spin_unlock(&pool->lock);
		z3fold_page_unlock(zhdr);
		return true;
	}
out:
	z3fold_page_unlock(zhdr);
	return false;
}