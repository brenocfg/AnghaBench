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
struct v9fs_inode {int /*<<< orphan*/  writeback_fid; } ;
struct page {int index; TYPE_1__* mapping; } ;
struct iov_iter {int dummy; } ;
struct inode {int dummy; } ;
struct bio_vec {int bv_len; scalar_t__ bv_offset; struct page* bv_page; } ;
typedef  int loff_t ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 struct v9fs_inode* V9FS_I (struct inode*) ; 
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  end_page_writeback (struct page*) ; 
 int i_size_read (struct inode*) ; 
 int /*<<< orphan*/  iov_iter_bvec (struct iov_iter*,int /*<<< orphan*/ ,struct bio_vec*,int,int) ; 
 int /*<<< orphan*/  p9_client_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iov_iter*,int*) ; 
 int /*<<< orphan*/  page_offset (struct page*) ; 
 int /*<<< orphan*/  set_page_writeback (struct page*) ; 

__attribute__((used)) static int v9fs_vfs_writepage_locked(struct page *page)
{
	struct inode *inode = page->mapping->host;
	struct v9fs_inode *v9inode = V9FS_I(inode);
	loff_t size = i_size_read(inode);
	struct iov_iter from;
	struct bio_vec bvec;
	int err, len;

	if (page->index == size >> PAGE_SHIFT)
		len = size & ~PAGE_MASK;
	else
		len = PAGE_SIZE;

	bvec.bv_page = page;
	bvec.bv_offset = 0;
	bvec.bv_len = len;
	iov_iter_bvec(&from, WRITE, &bvec, 1, len);

	/* We should have writeback_fid always set */
	BUG_ON(!v9inode->writeback_fid);

	set_page_writeback(page);

	p9_client_write(v9inode->writeback_fid, page_offset(page), &from, &err);

	end_page_writeback(page);
	return err;
}