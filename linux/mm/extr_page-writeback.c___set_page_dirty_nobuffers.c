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
struct page {int dummy; } ;
struct address_space {scalar_t__ host; int /*<<< orphan*/  i_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  I_DIRTY_PAGES ; 
 int /*<<< orphan*/  PAGECACHE_TAG_DIRTY ; 
 int /*<<< orphan*/  PagePrivate (struct page*) ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  TestSetPageDirty (struct page*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __mark_inode_dirty (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __xa_set_mark (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  account_page_dirtied (struct page*,struct address_space*) ; 
 int /*<<< orphan*/  lock_page_memcg (struct page*) ; 
 int /*<<< orphan*/  page_index (struct page*) ; 
 struct address_space* page_mapping (struct page*) ; 
 int /*<<< orphan*/  unlock_page_memcg (struct page*) ; 
 int /*<<< orphan*/  xa_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xa_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int __set_page_dirty_nobuffers(struct page *page)
{
	lock_page_memcg(page);
	if (!TestSetPageDirty(page)) {
		struct address_space *mapping = page_mapping(page);
		unsigned long flags;

		if (!mapping) {
			unlock_page_memcg(page);
			return 1;
		}

		xa_lock_irqsave(&mapping->i_pages, flags);
		BUG_ON(page_mapping(page) != mapping);
		WARN_ON_ONCE(!PagePrivate(page) && !PageUptodate(page));
		account_page_dirtied(page, mapping);
		__xa_set_mark(&mapping->i_pages, page_index(page),
				   PAGECACHE_TAG_DIRTY);
		xa_unlock_irqrestore(&mapping->i_pages, flags);
		unlock_page_memcg(page);

		if (mapping->host) {
			/* !PageAnon && !swapper_space */
			__mark_inode_dirty(mapping->host, I_DIRTY_PAGES);
		}
		return 1;
	}
	unlock_page_memcg(page);
	return 0;
}