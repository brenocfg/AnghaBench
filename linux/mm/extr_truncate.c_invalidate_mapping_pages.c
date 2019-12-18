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
struct page {int dummy; } ;
struct address_space {int dummy; } ;
typedef  scalar_t__ pgoff_t ;

/* Variables and functions */
 int HPAGE_PMD_NR ; 
 int PAGEVEC_SIZE ; 
 scalar_t__ PageTransHuge (struct page*) ; 
 scalar_t__ PageTransTail (struct page*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  deactivate_file_page (struct page*) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  invalidate_exceptional_entry (struct address_space*,scalar_t__,struct page*) ; 
 unsigned long invalidate_inode_page (struct page*) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 scalar_t__ page_to_index (struct page*) ; 
 int pagevec_count (struct pagevec*) ; 
 int /*<<< orphan*/  pagevec_init (struct pagevec*) ; 
 scalar_t__ pagevec_lookup_entries (struct pagevec*,struct address_space*,scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  pagevec_release (struct pagevec*) ; 
 int /*<<< orphan*/  pagevec_remove_exceptionals (struct pagevec*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  trylock_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 scalar_t__ xa_is_value (struct page*) ; 

unsigned long invalidate_mapping_pages(struct address_space *mapping,
		pgoff_t start, pgoff_t end)
{
	pgoff_t indices[PAGEVEC_SIZE];
	struct pagevec pvec;
	pgoff_t index = start;
	unsigned long ret;
	unsigned long count = 0;
	int i;

	pagevec_init(&pvec);
	while (index <= end && pagevec_lookup_entries(&pvec, mapping, index,
			min(end - index, (pgoff_t)PAGEVEC_SIZE - 1) + 1,
			indices)) {
		for (i = 0; i < pagevec_count(&pvec); i++) {
			struct page *page = pvec.pages[i];

			/* We rely upon deletion not changing page->index */
			index = indices[i];
			if (index > end)
				break;

			if (xa_is_value(page)) {
				invalidate_exceptional_entry(mapping, index,
							     page);
				continue;
			}

			if (!trylock_page(page))
				continue;

			WARN_ON(page_to_index(page) != index);

			/* Middle of THP: skip */
			if (PageTransTail(page)) {
				unlock_page(page);
				continue;
			} else if (PageTransHuge(page)) {
				index += HPAGE_PMD_NR - 1;
				i += HPAGE_PMD_NR - 1;
				/*
				 * 'end' is in the middle of THP. Don't
				 * invalidate the page as the part outside of
				 * 'end' could be still useful.
				 */
				if (index > end) {
					unlock_page(page);
					continue;
				}

				/* Take a pin outside pagevec */
				get_page(page);

				/*
				 * Drop extra pins before trying to invalidate
				 * the huge page.
				 */
				pagevec_remove_exceptionals(&pvec);
				pagevec_release(&pvec);
			}

			ret = invalidate_inode_page(page);
			unlock_page(page);
			/*
			 * Invalidation is a hint that the page is no longer
			 * of interest and try to speed up its reclaim.
			 */
			if (!ret)
				deactivate_file_page(page);
			if (PageTransHuge(page))
				put_page(page);
			count += ret;
		}
		pagevec_remove_exceptionals(&pvec);
		pagevec_release(&pvec);
		cond_resched();
		index++;
	}
	return count;
}