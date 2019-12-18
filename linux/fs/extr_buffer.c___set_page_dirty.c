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
struct page {scalar_t__ mapping; } ;
struct address_space {int /*<<< orphan*/  i_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGECACHE_TAG_DIRTY ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __xa_set_mark (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  account_page_dirtied (struct page*,struct address_space*) ; 
 int /*<<< orphan*/  page_index (struct page*) ; 
 int /*<<< orphan*/  xa_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xa_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void __set_page_dirty(struct page *page, struct address_space *mapping,
			     int warn)
{
	unsigned long flags;

	xa_lock_irqsave(&mapping->i_pages, flags);
	if (page->mapping) {	/* Race with truncate? */
		WARN_ON_ONCE(warn && !PageUptodate(page));
		account_page_dirtied(page, mapping);
		__xa_set_mark(&mapping->i_pages, page_index(page),
				PAGECACHE_TAG_DIRTY);
	}
	xa_unlock_irqrestore(&mapping->i_pages, flags);
}