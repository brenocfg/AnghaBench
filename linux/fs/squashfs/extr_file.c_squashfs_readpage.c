#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct squashfs_sb_info {int block_log; int block_size; } ;
struct page {int index; TYPE_1__* mapping; } ;
struct inode {TYPE_2__* i_sb; } ;
struct file {int dummy; } ;
struct TYPE_6__ {scalar_t__ fragment_block; int /*<<< orphan*/  start; } ;
struct TYPE_5__ {struct squashfs_sb_info* s_fs_info; } ;
struct TYPE_4__ {struct inode* host; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PageError (struct page*) ; 
 scalar_t__ SQUASHFS_INVALID_BLK ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  TRACE (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 int i_size_read (struct inode*) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int read_blocklist (struct inode*,int,int /*<<< orphan*/ *) ; 
 TYPE_3__* squashfs_i (struct inode*) ; 
 int squashfs_readpage_block (struct page*,int /*<<< orphan*/ ,int,int) ; 
 int squashfs_readpage_fragment (struct page*,int) ; 
 int squashfs_readpage_sparse (struct page*,int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int squashfs_readpage(struct file *file, struct page *page)
{
	struct inode *inode = page->mapping->host;
	struct squashfs_sb_info *msblk = inode->i_sb->s_fs_info;
	int index = page->index >> (msblk->block_log - PAGE_SHIFT);
	int file_end = i_size_read(inode) >> msblk->block_log;
	int expected = index == file_end ?
			(i_size_read(inode) & (msblk->block_size - 1)) :
			 msblk->block_size;
	int res;
	void *pageaddr;

	TRACE("Entered squashfs_readpage, page index %lx, start block %llx\n",
				page->index, squashfs_i(inode)->start);

	if (page->index >= ((i_size_read(inode) + PAGE_SIZE - 1) >>
					PAGE_SHIFT))
		goto out;

	if (index < file_end || squashfs_i(inode)->fragment_block ==
					SQUASHFS_INVALID_BLK) {
		u64 block = 0;
		int bsize = read_blocklist(inode, index, &block);
		if (bsize < 0)
			goto error_out;

		if (bsize == 0)
			res = squashfs_readpage_sparse(page, expected);
		else
			res = squashfs_readpage_block(page, block, bsize, expected);
	} else
		res = squashfs_readpage_fragment(page, expected);

	if (!res)
		return 0;

error_out:
	SetPageError(page);
out:
	pageaddr = kmap_atomic(page);
	memset(pageaddr, 0, PAGE_SIZE);
	kunmap_atomic(pageaddr);
	flush_dcache_page(page);
	if (!PageError(page))
		SetPageUptodate(page);
	unlock_page(page);

	return 0;
}