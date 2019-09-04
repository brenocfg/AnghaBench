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
struct z3fold_pool {int /*<<< orphan*/  unbuddied; int /*<<< orphan*/  lock; int /*<<< orphan*/  pages_nr; } ;
struct z3fold_header {int /*<<< orphan*/  cpu; int /*<<< orphan*/  buddy; int /*<<< orphan*/  last_chunks; int /*<<< orphan*/  middle_chunks; int /*<<< orphan*/  first_chunks; int /*<<< orphan*/  refcount; struct z3fold_pool* pool; } ;
struct page {int /*<<< orphan*/  private; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int NCHUNKS ; 
 int /*<<< orphan*/  NEEDS_COMPACTING ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  atomic64_dec (int /*<<< orphan*/ *) ; 
 struct list_head* get_cpu_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int num_free_chunks (struct z3fold_header*) ; 
 int /*<<< orphan*/  put_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_z3fold_page_locked ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct page* virt_to_page (struct z3fold_header*) ; 
 int /*<<< orphan*/  z3fold_compact_page (struct z3fold_header*) ; 
 int /*<<< orphan*/  z3fold_page_lock (struct z3fold_header*) ; 
 int z3fold_page_trylock (struct z3fold_header*) ; 
 int /*<<< orphan*/  z3fold_page_unlock (struct z3fold_header*) ; 

__attribute__((used)) static void do_compact_page(struct z3fold_header *zhdr, bool locked)
{
	struct z3fold_pool *pool = zhdr->pool;
	struct page *page;
	struct list_head *unbuddied;
	int fchunks;

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

	z3fold_compact_page(zhdr);
	unbuddied = get_cpu_ptr(pool->unbuddied);
	fchunks = num_free_chunks(zhdr);
	if (fchunks < NCHUNKS &&
	    (!zhdr->first_chunks || !zhdr->middle_chunks ||
			!zhdr->last_chunks)) {
		/* the page's not completely free and it's unbuddied */
		spin_lock(&pool->lock);
		list_add(&zhdr->buddy, &unbuddied[fchunks]);
		spin_unlock(&pool->lock);
		zhdr->cpu = smp_processor_id();
	}
	put_cpu_ptr(pool->unbuddied);
	z3fold_page_unlock(zhdr);
}