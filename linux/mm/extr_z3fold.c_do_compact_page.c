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
struct z3fold_pool {int /*<<< orphan*/  pages_nr; int /*<<< orphan*/  lock; } ;
struct z3fold_header {int /*<<< orphan*/  refcount; int /*<<< orphan*/  buddy; } ;
struct page {int /*<<< orphan*/  private; } ;

/* Variables and functions */
 int /*<<< orphan*/  NEEDS_COMPACTING ; 
 int /*<<< orphan*/  PAGE_CLAIMED ; 
 int /*<<< orphan*/  PAGE_STALE ; 
 scalar_t__ PageIsolated (struct page*) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  add_to_unbuddied (struct z3fold_pool*,struct z3fold_header*) ; 
 int /*<<< orphan*/  atomic64_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_z3fold_page_locked ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 struct page* virt_to_page (struct z3fold_header*) ; 
 int /*<<< orphan*/  z3fold_compact_page (struct z3fold_header*) ; 
 int /*<<< orphan*/  z3fold_page_lock (struct z3fold_header*) ; 
 int z3fold_page_trylock (struct z3fold_header*) ; 
 int /*<<< orphan*/  z3fold_page_unlock (struct z3fold_header*) ; 
 struct z3fold_pool* zhdr_to_pool (struct z3fold_header*) ; 

__attribute__((used)) static void do_compact_page(struct z3fold_header *zhdr, bool locked)
{
	struct z3fold_pool *pool = zhdr_to_pool(zhdr);
	struct page *page;

	page = virt_to_page(zhdr);
	if (locked)
		WARN_ON(z3fold_page_trylock(zhdr));
	else
		z3fold_page_lock(zhdr);
	if (WARN_ON(!test_and_clear_bit(NEEDS_COMPACTING, &page->private))) {
		z3fold_page_unlock(zhdr);
		return;
	}
	spin_lock(&pool->lock);
	list_del_init(&zhdr->buddy);
	spin_unlock(&pool->lock);

	if (kref_put(&zhdr->refcount, release_z3fold_page_locked)) {
		atomic64_dec(&pool->pages_nr);
		return;
	}

	if (unlikely(PageIsolated(page) ||
		     test_bit(PAGE_CLAIMED, &page->private) ||
		     test_bit(PAGE_STALE, &page->private))) {
		z3fold_page_unlock(zhdr);
		return;
	}

	z3fold_compact_page(zhdr);
	add_to_unbuddied(pool, zhdr);
	z3fold_page_unlock(zhdr);
}