#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct reiserfs_transaction_handle {int dummy; } ;
struct page {int dummy; } ;
struct inode {int i_size; TYPE_1__* i_sb; } ;
struct buffer_head {scalar_t__ b_blocknr; } ;
struct TYPE_5__ {unsigned int s_blocksize; } ;

/* Variables and functions */
 int ENOENT ; 
 int JOURNAL_PER_BALANCE_CNT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  add_save_link (struct reiserfs_transaction_handle*,struct inode*,int) ; 
 scalar_t__ buffer_mapped (struct buffer_head*) ; 
 int grab_tail_page (struct inode*,struct page**,struct buffer_head**) ; 
 int journal_begin (struct reiserfs_transaction_handle*,TYPE_1__*,int) ; 
 int journal_end (struct reiserfs_transaction_handle*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int reiserfs_do_truncate (struct reiserfs_transaction_handle*,struct inode*,struct page*,int) ; 
 int /*<<< orphan*/  reiserfs_error (TYPE_1__*,char*,char*,int) ; 
 int /*<<< orphan*/  reiserfs_update_inode_transaction (struct inode*) ; 
 int /*<<< orphan*/  reiserfs_write_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  reiserfs_write_unlock (TYPE_1__*) ; 
 int remove_save_link (struct inode*,int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  zero_user (struct page*,unsigned long,unsigned int) ; 

int reiserfs_truncate_file(struct inode *inode, int update_timestamps)
{
	struct reiserfs_transaction_handle th;
	/* we want the offset for the first byte after the end of the file */
	unsigned long offset = inode->i_size & (PAGE_SIZE - 1);
	unsigned blocksize = inode->i_sb->s_blocksize;
	unsigned length;
	struct page *page = NULL;
	int error;
	struct buffer_head *bh = NULL;
	int err2;

	reiserfs_write_lock(inode->i_sb);

	if (inode->i_size > 0) {
		error = grab_tail_page(inode, &page, &bh);
		if (error) {
			/*
			 * -ENOENT means we truncated past the end of the
			 * file, and get_block_create_0 could not find a
			 * block to read in, which is ok.
			 */
			if (error != -ENOENT)
				reiserfs_error(inode->i_sb, "clm-6001",
					       "grab_tail_page failed %d",
					       error);
			page = NULL;
			bh = NULL;
		}
	}

	/*
	 * so, if page != NULL, we have a buffer head for the offset at
	 * the end of the file. if the bh is mapped, and bh->b_blocknr != 0,
	 * then we have an unformatted node.  Otherwise, we have a direct item,
	 * and no zeroing is required on disk.  We zero after the truncate,
	 * because the truncate might pack the item anyway
	 * (it will unmap bh if it packs).
	 *
	 * it is enough to reserve space in transaction for 2 balancings:
	 * one for "save" link adding and another for the first
	 * cut_from_item. 1 is for update_sd
	 */
	error = journal_begin(&th, inode->i_sb,
			      JOURNAL_PER_BALANCE_CNT * 2 + 1);
	if (error)
		goto out;
	reiserfs_update_inode_transaction(inode);
	if (update_timestamps)
		/*
		 * we are doing real truncate: if the system crashes
		 * before the last transaction of truncating gets committed
		 * - on reboot the file either appears truncated properly
		 * or not truncated at all
		 */
		add_save_link(&th, inode, 1);
	err2 = reiserfs_do_truncate(&th, inode, page, update_timestamps);
	error = journal_end(&th);
	if (error)
		goto out;

	/* check reiserfs_do_truncate after ending the transaction */
	if (err2) {
		error = err2;
  		goto out;
	}
	
	if (update_timestamps) {
		error = remove_save_link(inode, 1 /* truncate */);
		if (error)
			goto out;
	}

	if (page) {
		length = offset & (blocksize - 1);
		/* if we are not on a block boundary */
		if (length) {
			length = blocksize - length;
			zero_user(page, offset, length);
			if (buffer_mapped(bh) && bh->b_blocknr != 0) {
				mark_buffer_dirty(bh);
			}
		}
		unlock_page(page);
		put_page(page);
	}

	reiserfs_write_unlock(inode->i_sb);

	return 0;
out:
	if (page) {
		unlock_page(page);
		put_page(page);
	}

	reiserfs_write_unlock(inode->i_sb);

	return error;
}