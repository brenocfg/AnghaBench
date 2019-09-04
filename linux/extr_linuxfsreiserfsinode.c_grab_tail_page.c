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
struct page {int dummy; } ;
struct inode {int i_size; TYPE_1__* i_sb; int /*<<< orphan*/  i_mapping; } ;
struct buffer_head {int /*<<< orphan*/  b_blocknr; struct buffer_head* b_this_page; } ;
struct TYPE_2__ {unsigned long s_blocksize; } ;

/* Variables and functions */
 int EIO ; 
 int ENOENT ; 
 int ENOMEM ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int __block_write_begin (struct page*,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 struct page* grab_cache_page (int /*<<< orphan*/ ,unsigned long) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  reiserfs_error (TYPE_1__*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_get_block_create_0 ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int grab_tail_page(struct inode *inode,
			  struct page **page_result,
			  struct buffer_head **bh_result)
{

	/*
	 * we want the page with the last byte in the file,
	 * not the page that will hold the next byte for appending
	 */
	unsigned long index = (inode->i_size - 1) >> PAGE_SHIFT;
	unsigned long pos = 0;
	unsigned long start = 0;
	unsigned long blocksize = inode->i_sb->s_blocksize;
	unsigned long offset = (inode->i_size) & (PAGE_SIZE - 1);
	struct buffer_head *bh;
	struct buffer_head *head;
	struct page *page;
	int error;

	/*
	 * we know that we are only called with inode->i_size > 0.
	 * we also know that a file tail can never be as big as a block
	 * If i_size % blocksize == 0, our file is currently block aligned
	 * and it won't need converting or zeroing after a truncate.
	 */
	if ((offset & (blocksize - 1)) == 0) {
		return -ENOENT;
	}
	page = grab_cache_page(inode->i_mapping, index);
	error = -ENOMEM;
	if (!page) {
		goto out;
	}
	/* start within the page of the last block in the file */
	start = (offset / blocksize) * blocksize;

	error = __block_write_begin(page, start, offset - start,
				    reiserfs_get_block_create_0);
	if (error)
		goto unlock;

	head = page_buffers(page);
	bh = head;
	do {
		if (pos >= start) {
			break;
		}
		bh = bh->b_this_page;
		pos += blocksize;
	} while (bh != head);

	if (!buffer_uptodate(bh)) {
		/*
		 * note, this should never happen, prepare_write should be
		 * taking care of this for us.  If the buffer isn't up to
		 * date, I've screwed up the code to find the buffer, or the
		 * code to call prepare_write
		 */
		reiserfs_error(inode->i_sb, "clm-6000",
			       "error reading block %lu", bh->b_blocknr);
		error = -EIO;
		goto unlock;
	}
	*bh_result = bh;
	*page_result = page;

out:
	return error;

unlock:
	unlock_page(page);
	put_page(page);
	return error;
}