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
struct address_space {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  I_DIRTY_PAGES ; 
 int /*<<< orphan*/  TestSetPageDirty (struct page*) ; 
 int /*<<< orphan*/  __mark_inode_dirty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_page_dirty (struct page*,struct address_space*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_page_memcg (struct page*) ; 
 struct address_space* page_mapping (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page_memcg (struct page*) ; 

int
iomap_set_page_dirty(struct page *page)
{
	struct address_space *mapping = page_mapping(page);
	int newly_dirty;

	if (unlikely(!mapping))
		return !TestSetPageDirty(page);

	/*
	 * Lock out page->mem_cgroup migration to keep PageDirty
	 * synchronized with per-memcg dirty page counters.
	 */
	lock_page_memcg(page);
	newly_dirty = !TestSetPageDirty(page);
	if (newly_dirty)
		__set_page_dirty(page, mapping, 0);
	unlock_page_memcg(page);

	if (newly_dirty)
		__mark_inode_dirty(mapping->host, I_DIRTY_PAGES);
	return newly_dirty;
}