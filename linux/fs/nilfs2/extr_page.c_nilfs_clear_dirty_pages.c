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
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGECACHE_TAG_DIRTY ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  nilfs_clear_dirty_page (struct page*,int) ; 
 unsigned int pagevec_count (struct pagevec*) ; 
 int /*<<< orphan*/  pagevec_init (struct pagevec*) ; 
 scalar_t__ pagevec_lookup_tag (struct pagevec*,struct address_space*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pagevec_release (struct pagevec*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

void nilfs_clear_dirty_pages(struct address_space *mapping, bool silent)
{
	struct pagevec pvec;
	unsigned int i;
	pgoff_t index = 0;

	pagevec_init(&pvec);

	while (pagevec_lookup_tag(&pvec, mapping, &index,
					PAGECACHE_TAG_DIRTY)) {
		for (i = 0; i < pagevec_count(&pvec); i++) {
			struct page *page = pvec.pages[i];

			lock_page(page);
			nilfs_clear_dirty_page(page, silent);
			unlock_page(page);
		}
		pagevec_release(&pvec);
		cond_resched();
	}
}