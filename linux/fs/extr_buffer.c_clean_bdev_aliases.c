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
struct inode {int i_blkbits; struct address_space* i_mapping; } ;
struct buffer_head {int b_blocknr; struct buffer_head* b_this_page; } ;
struct block_device {struct inode* bd_inode; } ;
struct address_space {int dummy; } ;
typedef  int sector_t ;
typedef  int pgoff_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_req (struct buffer_head*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 int /*<<< orphan*/  page_has_buffers (struct page*) ; 
 int pagevec_count (struct pagevec*) ; 
 int /*<<< orphan*/  pagevec_init (struct pagevec*) ; 
 scalar_t__ pagevec_lookup_range (struct pagevec*,struct address_space*,int*,int) ; 
 int /*<<< orphan*/  pagevec_release (struct pagevec*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 

void clean_bdev_aliases(struct block_device *bdev, sector_t block, sector_t len)
{
	struct inode *bd_inode = bdev->bd_inode;
	struct address_space *bd_mapping = bd_inode->i_mapping;
	struct pagevec pvec;
	pgoff_t index = block >> (PAGE_SHIFT - bd_inode->i_blkbits);
	pgoff_t end;
	int i, count;
	struct buffer_head *bh;
	struct buffer_head *head;

	end = (block + len - 1) >> (PAGE_SHIFT - bd_inode->i_blkbits);
	pagevec_init(&pvec);
	while (pagevec_lookup_range(&pvec, bd_mapping, &index, end)) {
		count = pagevec_count(&pvec);
		for (i = 0; i < count; i++) {
			struct page *page = pvec.pages[i];

			if (!page_has_buffers(page))
				continue;
			/*
			 * We use page lock instead of bd_mapping->private_lock
			 * to pin buffers here since we can afford to sleep and
			 * it scales better than a global spinlock lock.
			 */
			lock_page(page);
			/* Recheck when the page is locked which pins bhs */
			if (!page_has_buffers(page))
				goto unlock_page;
			head = page_buffers(page);
			bh = head;
			do {
				if (!buffer_mapped(bh) || (bh->b_blocknr < block))
					goto next;
				if (bh->b_blocknr >= block + len)
					break;
				clear_buffer_dirty(bh);
				wait_on_buffer(bh);
				clear_buffer_req(bh);
next:
				bh = bh->b_this_page;
			} while (bh != head);
unlock_page:
			unlock_page(page);
		}
		pagevec_release(&pvec);
		cond_resched();
		/* End of range already reached? */
		if (index > end || !index)
			break;
	}
}