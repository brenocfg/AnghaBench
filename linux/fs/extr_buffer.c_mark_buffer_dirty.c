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
struct buffer_head {struct page* b_page; } ;
struct address_space {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  I_DIRTY_PAGES ; 
 int /*<<< orphan*/  TestSetPageDirty (struct page*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __mark_inode_dirty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_page_dirty (struct page*,struct address_space*,int /*<<< orphan*/ ) ; 
 scalar_t__ buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  lock_page_memcg (struct page*) ; 
 struct address_space* page_mapping (struct page*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  test_set_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  trace_block_dirty_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_page_memcg (struct page*) ; 

void mark_buffer_dirty(struct buffer_head *bh)
{
	WARN_ON_ONCE(!buffer_uptodate(bh));

	trace_block_dirty_buffer(bh);

	/*
	 * Very *carefully* optimize the it-is-already-dirty case.
	 *
	 * Don't let the final "is it dirty" escape to before we
	 * perhaps modified the buffer.
	 */
	if (buffer_dirty(bh)) {
		smp_mb();
		if (buffer_dirty(bh))
			return;
	}

	if (!test_set_buffer_dirty(bh)) {
		struct page *page = bh->b_page;
		struct address_space *mapping = NULL;

		lock_page_memcg(page);
		if (!TestSetPageDirty(page)) {
			mapping = page_mapping(page);
			if (mapping)
				__set_page_dirty(page, mapping, 0);
		}
		unlock_page_memcg(page);
		if (mapping)
			__mark_inode_dirty(mapping->host, I_DIRTY_PAGES);
	}
}