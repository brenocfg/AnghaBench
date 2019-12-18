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
struct z3fold_pool {int /*<<< orphan*/  compact_wq; int /*<<< orphan*/  lock; int /*<<< orphan*/  lru; } ;
struct z3fold_header {scalar_t__ mapped_count; int /*<<< orphan*/  work; int /*<<< orphan*/  cpu; scalar_t__ middle_chunks; scalar_t__ last_chunks; scalar_t__ first_chunks; int /*<<< orphan*/  buddy; int /*<<< orphan*/  page_lock; } ;
struct page {int /*<<< orphan*/  lru; scalar_t__ private; } ;
struct address_space {int dummy; } ;
typedef  enum migrate_mode { ____Placeholder_migrate_mode } migrate_mode ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPagePrivate (struct page*) ; 
 int EAGAIN ; 
 int EBUSY ; 
 int /*<<< orphan*/  FIRST ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LAST ; 
 int /*<<< orphan*/  MIDDLE ; 
 int /*<<< orphan*/  NEEDS_COMPACTING ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PageIsolated (struct page*) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  PageMovable (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  __ClearPageMovable (struct page*) ; 
 int /*<<< orphan*/  __SetPageMovable (struct page*,struct address_space*) ; 
 int /*<<< orphan*/  compact_page_work ; 
 int /*<<< orphan*/  encode_handle (struct z3fold_header*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct z3fold_header*,struct z3fold_header*,int /*<<< orphan*/ ) ; 
 struct z3fold_header* page_address (struct page*) ; 
 int /*<<< orphan*/  page_mapcount_reset (struct page*) ; 
 struct address_space* page_mapping (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  queue_work_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ work_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  z3fold_page_lock (struct z3fold_header*) ; 
 int /*<<< orphan*/  z3fold_page_trylock (struct z3fold_header*) ; 
 int /*<<< orphan*/  z3fold_page_unlock (struct z3fold_header*) ; 
 struct z3fold_pool* zhdr_to_pool (struct z3fold_header*) ; 

__attribute__((used)) static int z3fold_page_migrate(struct address_space *mapping, struct page *newpage,
			       struct page *page, enum migrate_mode mode)
{
	struct z3fold_header *zhdr, *new_zhdr;
	struct z3fold_pool *pool;
	struct address_space *new_mapping;

	VM_BUG_ON_PAGE(!PageMovable(page), page);
	VM_BUG_ON_PAGE(!PageIsolated(page), page);
	VM_BUG_ON_PAGE(!PageLocked(newpage), newpage);

	zhdr = page_address(page);
	pool = zhdr_to_pool(zhdr);

	if (!z3fold_page_trylock(zhdr)) {
		return -EAGAIN;
	}
	if (zhdr->mapped_count != 0) {
		z3fold_page_unlock(zhdr);
		return -EBUSY;
	}
	if (work_pending(&zhdr->work)) {
		z3fold_page_unlock(zhdr);
		return -EAGAIN;
	}
	new_zhdr = page_address(newpage);
	memcpy(new_zhdr, zhdr, PAGE_SIZE);
	newpage->private = page->private;
	page->private = 0;
	z3fold_page_unlock(zhdr);
	spin_lock_init(&new_zhdr->page_lock);
	INIT_WORK(&new_zhdr->work, compact_page_work);
	/*
	 * z3fold_page_isolate() ensures that new_zhdr->buddy is empty,
	 * so we only have to reinitialize it.
	 */
	INIT_LIST_HEAD(&new_zhdr->buddy);
	new_mapping = page_mapping(page);
	__ClearPageMovable(page);
	ClearPagePrivate(page);

	get_page(newpage);
	z3fold_page_lock(new_zhdr);
	if (new_zhdr->first_chunks)
		encode_handle(new_zhdr, FIRST);
	if (new_zhdr->last_chunks)
		encode_handle(new_zhdr, LAST);
	if (new_zhdr->middle_chunks)
		encode_handle(new_zhdr, MIDDLE);
	set_bit(NEEDS_COMPACTING, &newpage->private);
	new_zhdr->cpu = smp_processor_id();
	spin_lock(&pool->lock);
	list_add(&newpage->lru, &pool->lru);
	spin_unlock(&pool->lock);
	__SetPageMovable(newpage, new_mapping);
	z3fold_page_unlock(new_zhdr);

	queue_work_on(new_zhdr->cpu, pool->compact_wq, &new_zhdr->work);

	page_mapcount_reset(page);
	put_page(page);
	return 0;
}