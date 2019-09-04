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
struct pipe_inode_info {int dummy; } ;
struct pipe_buffer {int /*<<< orphan*/  flags; struct page* page; } ;
struct page {int dummy; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PIPE_BUF_FLAG_LRU ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 scalar_t__ page_has_private (struct page*) ; 
 struct address_space* page_mapping (struct page*) ; 
 scalar_t__ remove_mapping (struct address_space*,struct page*) ; 
 int /*<<< orphan*/  try_to_release_page (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  wait_on_page_writeback (struct page*) ; 

__attribute__((used)) static int page_cache_pipe_buf_steal(struct pipe_inode_info *pipe,
				     struct pipe_buffer *buf)
{
	struct page *page = buf->page;
	struct address_space *mapping;

	lock_page(page);

	mapping = page_mapping(page);
	if (mapping) {
		WARN_ON(!PageUptodate(page));

		/*
		 * At least for ext2 with nobh option, we need to wait on
		 * writeback completing on this page, since we'll remove it
		 * from the pagecache.  Otherwise truncate wont wait on the
		 * page, allowing the disk blocks to be reused by someone else
		 * before we actually wrote our data to them. fs corruption
		 * ensues.
		 */
		wait_on_page_writeback(page);

		if (page_has_private(page) &&
		    !try_to_release_page(page, GFP_KERNEL))
			goto out_unlock;

		/*
		 * If we succeeded in removing the mapping, set LRU flag
		 * and return good.
		 */
		if (remove_mapping(mapping, page)) {
			buf->flags |= PIPE_BUF_FLAG_LRU;
			return 0;
		}
	}

	/*
	 * Raced with truncate or failed to remove page from current
	 * address space, unlock and return failure.
	 */
out_unlock:
	unlock_page(page);
	return 1;
}