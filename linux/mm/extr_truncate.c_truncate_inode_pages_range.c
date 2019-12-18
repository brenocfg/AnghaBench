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
struct pagevec {struct page** pages; } ;
struct page {struct address_space* mapping; } ;
struct address_space {scalar_t__ nrpages; scalar_t__ nrexceptional; } ;
typedef  int pgoff_t ;
typedef  int loff_t ;

/* Variables and functions */
 int PAGEVEC_SIZE ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 scalar_t__ PageWriteback (struct page*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cleancache_invalidate_inode (struct address_space*) ; 
 int /*<<< orphan*/  cleancache_invalidate_page (struct address_space*,struct page*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  delete_from_page_cache_batch (struct address_space*,struct pagevec*) ; 
 int /*<<< orphan*/  do_invalidatepage (struct page*,unsigned int,unsigned int) ; 
 struct page* find_lock_page (struct address_space*,int) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  min (int,int) ; 
 scalar_t__ page_has_private (struct page*) ; 
 int page_to_index (struct page*) ; 
 int /*<<< orphan*/  pagevec_add (struct pagevec*,struct page*) ; 
 int pagevec_count (struct pagevec*) ; 
 int /*<<< orphan*/  pagevec_init (struct pagevec*) ; 
 scalar_t__ pagevec_lookup_entries (struct pagevec*,struct address_space*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pagevec_release (struct pagevec*) ; 
 int /*<<< orphan*/  pagevec_remove_exceptionals (struct pagevec*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  truncate_cleanup_page (struct address_space*,struct page*) ; 
 int /*<<< orphan*/  truncate_exceptional_pvec_entries (struct address_space*,struct pagevec*,int*,int) ; 
 int /*<<< orphan*/  truncate_inode_page (struct address_space*,struct page*) ; 
 int /*<<< orphan*/  trylock_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  wait_on_page_writeback (struct page*) ; 
 scalar_t__ xa_is_value (struct page*) ; 
 int /*<<< orphan*/  zero_user_segment (struct page*,unsigned int,unsigned int) ; 

void truncate_inode_pages_range(struct address_space *mapping,
				loff_t lstart, loff_t lend)
{
	pgoff_t		start;		/* inclusive */
	pgoff_t		end;		/* exclusive */
	unsigned int	partial_start;	/* inclusive */
	unsigned int	partial_end;	/* exclusive */
	struct pagevec	pvec;
	pgoff_t		indices[PAGEVEC_SIZE];
	pgoff_t		index;
	int		i;

	if (mapping->nrpages == 0 && mapping->nrexceptional == 0)
		goto out;

	/* Offsets within partial pages */
	partial_start = lstart & (PAGE_SIZE - 1);
	partial_end = (lend + 1) & (PAGE_SIZE - 1);

	/*
	 * 'start' and 'end' always covers the range of pages to be fully
	 * truncated. Partial pages are covered with 'partial_start' at the
	 * start of the range and 'partial_end' at the end of the range.
	 * Note that 'end' is exclusive while 'lend' is inclusive.
	 */
	start = (lstart + PAGE_SIZE - 1) >> PAGE_SHIFT;
	if (lend == -1)
		/*
		 * lend == -1 indicates end-of-file so we have to set 'end'
		 * to the highest possible pgoff_t and since the type is
		 * unsigned we're using -1.
		 */
		end = -1;
	else
		end = (lend + 1) >> PAGE_SHIFT;

	pagevec_init(&pvec);
	index = start;
	while (index < end && pagevec_lookup_entries(&pvec, mapping, index,
			min(end - index, (pgoff_t)PAGEVEC_SIZE),
			indices)) {
		/*
		 * Pagevec array has exceptional entries and we may also fail
		 * to lock some pages. So we store pages that can be deleted
		 * in a new pagevec.
		 */
		struct pagevec locked_pvec;

		pagevec_init(&locked_pvec);
		for (i = 0; i < pagevec_count(&pvec); i++) {
			struct page *page = pvec.pages[i];

			/* We rely upon deletion not changing page->index */
			index = indices[i];
			if (index >= end)
				break;

			if (xa_is_value(page))
				continue;

			if (!trylock_page(page))
				continue;
			WARN_ON(page_to_index(page) != index);
			if (PageWriteback(page)) {
				unlock_page(page);
				continue;
			}
			if (page->mapping != mapping) {
				unlock_page(page);
				continue;
			}
			pagevec_add(&locked_pvec, page);
		}
		for (i = 0; i < pagevec_count(&locked_pvec); i++)
			truncate_cleanup_page(mapping, locked_pvec.pages[i]);
		delete_from_page_cache_batch(mapping, &locked_pvec);
		for (i = 0; i < pagevec_count(&locked_pvec); i++)
			unlock_page(locked_pvec.pages[i]);
		truncate_exceptional_pvec_entries(mapping, &pvec, indices, end);
		pagevec_release(&pvec);
		cond_resched();
		index++;
	}
	if (partial_start) {
		struct page *page = find_lock_page(mapping, start - 1);
		if (page) {
			unsigned int top = PAGE_SIZE;
			if (start > end) {
				/* Truncation within a single page */
				top = partial_end;
				partial_end = 0;
			}
			wait_on_page_writeback(page);
			zero_user_segment(page, partial_start, top);
			cleancache_invalidate_page(mapping, page);
			if (page_has_private(page))
				do_invalidatepage(page, partial_start,
						  top - partial_start);
			unlock_page(page);
			put_page(page);
		}
	}
	if (partial_end) {
		struct page *page = find_lock_page(mapping, end);
		if (page) {
			wait_on_page_writeback(page);
			zero_user_segment(page, 0, partial_end);
			cleancache_invalidate_page(mapping, page);
			if (page_has_private(page))
				do_invalidatepage(page, 0,
						  partial_end);
			unlock_page(page);
			put_page(page);
		}
	}
	/*
	 * If the truncation happened within a single page no pages
	 * will be released, just zeroed, so we can bail out now.
	 */
	if (start >= end)
		goto out;

	index = start;
	for ( ; ; ) {
		cond_resched();
		if (!pagevec_lookup_entries(&pvec, mapping, index,
			min(end - index, (pgoff_t)PAGEVEC_SIZE), indices)) {
			/* If all gone from start onwards, we're done */
			if (index == start)
				break;
			/* Otherwise restart to make sure all gone */
			index = start;
			continue;
		}
		if (index == start && indices[0] >= end) {
			/* All gone out of hole to be punched, we're done */
			pagevec_remove_exceptionals(&pvec);
			pagevec_release(&pvec);
			break;
		}

		for (i = 0; i < pagevec_count(&pvec); i++) {
			struct page *page = pvec.pages[i];

			/* We rely upon deletion not changing page->index */
			index = indices[i];
			if (index >= end) {
				/* Restart punch to make sure all gone */
				index = start - 1;
				break;
			}

			if (xa_is_value(page))
				continue;

			lock_page(page);
			WARN_ON(page_to_index(page) != index);
			wait_on_page_writeback(page);
			truncate_inode_page(mapping, page);
			unlock_page(page);
		}
		truncate_exceptional_pvec_entries(mapping, &pvec, indices, end);
		pagevec_release(&pvec);
		index++;
	}

out:
	cleancache_invalidate_inode(mapping);
}