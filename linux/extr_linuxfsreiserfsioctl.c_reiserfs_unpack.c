#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct inode {unsigned long i_size; TYPE_1__* i_sb; struct address_space* i_mapping; } ;
struct file {int dummy; } ;
struct address_space {int dummy; } ;
struct TYPE_7__ {int i_flags; } ;
struct TYPE_6__ {unsigned long s_blocksize; } ;

/* Variables and functions */
 int ENOMEM ; 
 int PAGE_SHIFT ; 
 TYPE_5__* REISERFS_I (struct inode*) ; 
 int __reiserfs_write_begin (struct page*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 struct page* grab_cache_page (struct address_space*,int) ; 
 int i_nopack_mask ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int reiserfs_commit_write (int /*<<< orphan*/ *,struct page*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  reiserfs_write_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  reiserfs_write_lock_nested (TYPE_1__*,int) ; 
 int /*<<< orphan*/  reiserfs_write_unlock (TYPE_1__*) ; 
 int reiserfs_write_unlock_nested (TYPE_1__*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int reiserfs_unpack(struct inode *inode, struct file *filp)
{
	int retval = 0;
	int index;
	struct page *page;
	struct address_space *mapping;
	unsigned long write_from;
	unsigned long blocksize = inode->i_sb->s_blocksize;

	if (inode->i_size == 0) {
		REISERFS_I(inode)->i_flags |= i_nopack_mask;
		return 0;
	}
	/* ioctl already done */
	if (REISERFS_I(inode)->i_flags & i_nopack_mask) {
		return 0;
	}

	/* we need to make sure nobody is changing the file size beneath us */
{
	int depth = reiserfs_write_unlock_nested(inode->i_sb);
	inode_lock(inode);
	reiserfs_write_lock_nested(inode->i_sb, depth);
}

	reiserfs_write_lock(inode->i_sb);

	write_from = inode->i_size & (blocksize - 1);
	/* if we are on a block boundary, we are already unpacked.  */
	if (write_from == 0) {
		REISERFS_I(inode)->i_flags |= i_nopack_mask;
		goto out;
	}

	/*
	 * we unpack by finding the page with the tail, and calling
	 * __reiserfs_write_begin on that page.  This will force a
	 * reiserfs_get_block to unpack the tail for us.
	 */
	index = inode->i_size >> PAGE_SHIFT;
	mapping = inode->i_mapping;
	page = grab_cache_page(mapping, index);
	retval = -ENOMEM;
	if (!page) {
		goto out;
	}
	retval = __reiserfs_write_begin(page, write_from, 0);
	if (retval)
		goto out_unlock;

	/* conversion can change page contents, must flush */
	flush_dcache_page(page);
	retval = reiserfs_commit_write(NULL, page, write_from, write_from);
	REISERFS_I(inode)->i_flags |= i_nopack_mask;

out_unlock:
	unlock_page(page);
	put_page(page);

out:
	inode_unlock(inode);
	reiserfs_write_unlock(inode->i_sb);
	return retval;
}