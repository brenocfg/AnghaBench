#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {scalar_t__ index; TYPE_1__* mapping; } ;
struct inode {int i_blkbits; } ;
struct buffer_head {struct buffer_head* b_this_page; } ;
typedef  int sector_t ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int MAX_BUF_PER_PAGE ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 scalar_t__ PageUptodate (struct page*) ; 
 int PageWriteback (struct page*) ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int bh_submit_read (struct buffer_head*) ; 
 int /*<<< orphan*/  bh_uptodate_or_lock (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_mapped (struct buffer_head*) ; 
 scalar_t__ buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  create_empty_buffers (struct page*,unsigned int,int /*<<< orphan*/ ) ; 
 int ext4_get_block (struct inode*,int,struct buffer_head*,int /*<<< orphan*/ ) ; 
 unsigned int i_blocksize (struct inode*) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 int /*<<< orphan*/  page_has_buffers (struct page*) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  zero_user (struct page*,unsigned int,unsigned int) ; 

__attribute__((used)) static int
mext_page_mkuptodate(struct page *page, unsigned from, unsigned to)
{
	struct inode *inode = page->mapping->host;
	sector_t block;
	struct buffer_head *bh, *head, *arr[MAX_BUF_PER_PAGE];
	unsigned int blocksize, block_start, block_end;
	int i, err,  nr = 0, partial = 0;
	BUG_ON(!PageLocked(page));
	BUG_ON(PageWriteback(page));

	if (PageUptodate(page))
		return 0;

	blocksize = i_blocksize(inode);
	if (!page_has_buffers(page))
		create_empty_buffers(page, blocksize, 0);

	head = page_buffers(page);
	block = (sector_t)page->index << (PAGE_SHIFT - inode->i_blkbits);
	for (bh = head, block_start = 0; bh != head || !block_start;
	     block++, block_start = block_end, bh = bh->b_this_page) {
		block_end = block_start + blocksize;
		if (block_end <= from || block_start >= to) {
			if (!buffer_uptodate(bh))
				partial = 1;
			continue;
		}
		if (buffer_uptodate(bh))
			continue;
		if (!buffer_mapped(bh)) {
			err = ext4_get_block(inode, block, bh, 0);
			if (err) {
				SetPageError(page);
				return err;
			}
			if (!buffer_mapped(bh)) {
				zero_user(page, block_start, blocksize);
				set_buffer_uptodate(bh);
				continue;
			}
		}
		BUG_ON(nr >= MAX_BUF_PER_PAGE);
		arr[nr++] = bh;
	}
	/* No io required */
	if (!nr)
		goto out;

	for (i = 0; i < nr; i++) {
		bh = arr[i];
		if (!bh_uptodate_or_lock(bh)) {
			err = bh_submit_read(bh);
			if (err)
				return err;
		}
	}
out:
	if (!partial)
		SetPageUptodate(page);
	return 0;
}