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
struct z3fold_pool {int /*<<< orphan*/  lock; int /*<<< orphan*/  lru; int /*<<< orphan*/  pages_nr; } ;
struct z3fold_header {int /*<<< orphan*/  refcount; int /*<<< orphan*/  buddy; } ;
struct page {int /*<<< orphan*/  lru; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic64_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct z3fold_header* page_address (struct page*) ; 
 int /*<<< orphan*/  release_z3fold_page_locked ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  z3fold_page_lock (struct z3fold_header*) ; 
 int /*<<< orphan*/  z3fold_page_unlock (struct z3fold_header*) ; 
 struct z3fold_pool* zhdr_to_pool (struct z3fold_header*) ; 

__attribute__((used)) static void z3fold_page_putback(struct page *page)
{
	struct z3fold_header *zhdr;
	struct z3fold_pool *pool;

	zhdr = page_address(page);
	pool = zhdr_to_pool(zhdr);

	z3fold_page_lock(zhdr);
	if (!list_empty(&zhdr->buddy))
		list_del_init(&zhdr->buddy);
	INIT_LIST_HEAD(&page->lru);
	if (kref_put(&zhdr->refcount, release_z3fold_page_locked)) {
		atomic64_dec(&pool->pages_nr);
		return;
	}
	spin_lock(&pool->lock);
	list_add(&page->lru, &pool->lru);
	spin_unlock(&pool->lock);
	z3fold_page_unlock(zhdr);
}