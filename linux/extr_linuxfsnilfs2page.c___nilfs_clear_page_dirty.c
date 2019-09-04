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
struct page {int /*<<< orphan*/  flags; struct address_space* mapping; } ;
struct address_space {int /*<<< orphan*/  i_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGECACHE_TAG_DIRTY ; 
 int /*<<< orphan*/  PG_dirty ; 
 int TestClearPageDirty (struct page*) ; 
 int clear_page_dirty_for_io (struct page*) ; 
 int /*<<< orphan*/  page_index (struct page*) ; 
 int /*<<< orphan*/  radix_tree_tag_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_unlock_irq (int /*<<< orphan*/ *) ; 

int __nilfs_clear_page_dirty(struct page *page)
{
	struct address_space *mapping = page->mapping;

	if (mapping) {
		xa_lock_irq(&mapping->i_pages);
		if (test_bit(PG_dirty, &page->flags)) {
			radix_tree_tag_clear(&mapping->i_pages,
					     page_index(page),
					     PAGECACHE_TAG_DIRTY);
			xa_unlock_irq(&mapping->i_pages);
			return clear_page_dirty_for_io(page);
		}
		xa_unlock_irq(&mapping->i_pages);
		return 0;
	}
	return TestClearPageDirty(page);
}