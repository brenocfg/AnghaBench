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
struct page {struct address_space* mapping; int /*<<< orphan*/  index; } ;
struct address_space {int /*<<< orphan*/  i_pages; int /*<<< orphan*/  nrpages; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  PAGECACHE_TAG_DIRTY ; 
 int PageDirty (struct page*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct page* __xa_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __xa_set_mark (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct page* __xa_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cond_resched () ; 
 struct page* find_lock_page (struct address_space*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  nilfs_copy_page (struct page*,struct page*,int /*<<< orphan*/ ) ; 
 unsigned int pagevec_count (struct pagevec*) ; 
 int /*<<< orphan*/  pagevec_init (struct pagevec*) ; 
 unsigned int pagevec_lookup (struct pagevec*,struct address_space*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pagevec_release (struct pagevec*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 scalar_t__ unlikely (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  xa_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_unlock_irq (int /*<<< orphan*/ *) ; 

void nilfs_copy_back_pages(struct address_space *dmap,
			   struct address_space *smap)
{
	struct pagevec pvec;
	unsigned int i, n;
	pgoff_t index = 0;

	pagevec_init(&pvec);
repeat:
	n = pagevec_lookup(&pvec, smap, &index);
	if (!n)
		return;

	for (i = 0; i < pagevec_count(&pvec); i++) {
		struct page *page = pvec.pages[i], *dpage;
		pgoff_t offset = page->index;

		lock_page(page);
		dpage = find_lock_page(dmap, offset);
		if (dpage) {
			/* overwrite existing page in the destination cache */
			WARN_ON(PageDirty(dpage));
			nilfs_copy_page(dpage, page, 0);
			unlock_page(dpage);
			put_page(dpage);
			/* Do we not need to remove page from smap here? */
		} else {
			struct page *p;

			/* move the page to the destination cache */
			xa_lock_irq(&smap->i_pages);
			p = __xa_erase(&smap->i_pages, offset);
			WARN_ON(page != p);
			smap->nrpages--;
			xa_unlock_irq(&smap->i_pages);

			xa_lock_irq(&dmap->i_pages);
			p = __xa_store(&dmap->i_pages, offset, page, GFP_NOFS);
			if (unlikely(p)) {
				/* Probably -ENOMEM */
				page->mapping = NULL;
				put_page(page);
			} else {
				page->mapping = dmap;
				dmap->nrpages++;
				if (PageDirty(page))
					__xa_set_mark(&dmap->i_pages, offset,
							PAGECACHE_TAG_DIRTY);
			}
			xa_unlock_irq(&dmap->i_pages);
		}
		unlock_page(page);
	}
	pagevec_release(&pvec);
	cond_resched();

	goto repeat;
}