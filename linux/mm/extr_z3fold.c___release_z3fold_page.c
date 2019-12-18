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
struct z3fold_pool {int /*<<< orphan*/  stale_lock; int /*<<< orphan*/  work; int /*<<< orphan*/  release_wq; int /*<<< orphan*/  stale; int /*<<< orphan*/  lock; } ;
struct z3fold_header {int /*<<< orphan*/  buddy; } ;
struct page {int /*<<< orphan*/  lru; int /*<<< orphan*/  private; } ;

/* Variables and functions */
 int /*<<< orphan*/  NEEDS_COMPACTING ; 
 int /*<<< orphan*/  PAGE_STALE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct page* virt_to_page (struct z3fold_header*) ; 
 int /*<<< orphan*/  z3fold_page_unlock (struct z3fold_header*) ; 
 struct z3fold_pool* zhdr_to_pool (struct z3fold_header*) ; 

__attribute__((used)) static void __release_z3fold_page(struct z3fold_header *zhdr, bool locked)
{
	struct page *page = virt_to_page(zhdr);
	struct z3fold_pool *pool = zhdr_to_pool(zhdr);

	WARN_ON(!list_empty(&zhdr->buddy));
	set_bit(PAGE_STALE, &page->private);
	clear_bit(NEEDS_COMPACTING, &page->private);
	spin_lock(&pool->lock);
	if (!list_empty(&page->lru))
		list_del_init(&page->lru);
	spin_unlock(&pool->lock);
	if (locked)
		z3fold_page_unlock(zhdr);
	spin_lock(&pool->stale_lock);
	list_add(&zhdr->buddy, &pool->stale);
	queue_work(pool->release_wq, &pool->work);
	spin_unlock(&pool->stale_lock);
}