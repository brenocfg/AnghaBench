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
struct buffer_head {struct buffer_head* b_this_page; } ;
struct address_space {int /*<<< orphan*/  host; int /*<<< orphan*/  private_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  I_DIRTY_PAGES ; 
 int /*<<< orphan*/  TestSetPageDirty (struct page*) ; 
 int /*<<< orphan*/  __mark_inode_dirty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_page_dirty (struct page*,struct address_space*,int) ; 
 int /*<<< orphan*/  lock_page_memcg (struct page*) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 scalar_t__ page_has_buffers (struct page*) ; 
 struct address_space* page_mapping (struct page*) ; 
 int /*<<< orphan*/  set_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page_memcg (struct page*) ; 

int __set_page_dirty_buffers(struct page *page)
{
	int newly_dirty;
	struct address_space *mapping = page_mapping(page);

	if (unlikely(!mapping))
		return !TestSetPageDirty(page);

	spin_lock(&mapping->private_lock);
	if (page_has_buffers(page)) {
		struct buffer_head *head = page_buffers(page);
		struct buffer_head *bh = head;

		do {
			set_buffer_dirty(bh);
			bh = bh->b_this_page;
		} while (bh != head);
	}
	/*
	 * Lock out page->mem_cgroup migration to keep PageDirty
	 * synchronized with per-memcg dirty page counters.
	 */
	lock_page_memcg(page);
	newly_dirty = !TestSetPageDirty(page);
	spin_unlock(&mapping->private_lock);

	if (newly_dirty)
		__set_page_dirty(page, mapping, 1);

	unlock_page_memcg(page);

	if (newly_dirty)
		__mark_inode_dirty(mapping->host, I_DIRTY_PAGES);

	return newly_dirty;
}