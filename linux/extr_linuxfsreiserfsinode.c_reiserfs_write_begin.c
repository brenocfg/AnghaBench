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
struct reiserfs_transaction_handle {int t_refcount; int /*<<< orphan*/  t_trans_id; } ;
struct page {int dummy; } ;
struct inode {TYPE_1__* i_sb; } ;
struct file {int dummy; } ;
struct address_space {struct inode* host; } ;
typedef  int pgoff_t ;
typedef  int loff_t ;
struct TYPE_7__ {struct reiserfs_transaction_handle* journal_info; } ;
struct TYPE_6__ {int s_blocksize; } ;

/* Variables and functions */
 unsigned int AOP_FLAG_CONT_EXPAND ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int PAGE_SHIFT ; 
 int __block_write_begin (struct page*,int,unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_5__* current ; 
 int /*<<< orphan*/  fix_tail_page_for_writing (struct page*) ; 
 struct page* grab_cache_page_write_begin (struct address_space*,int,unsigned int) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int reiserfs_end_persistent_transaction (struct reiserfs_transaction_handle*) ; 
 int /*<<< orphan*/  reiserfs_get_block ; 
 scalar_t__ reiserfs_transaction_running (TYPE_1__*) ; 
 int /*<<< orphan*/  reiserfs_truncate_failed_write (struct inode*) ; 
 int /*<<< orphan*/  reiserfs_wait_on_write_block (TYPE_1__*) ; 
 int /*<<< orphan*/  reiserfs_write_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  reiserfs_write_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int reiserfs_write_begin(struct file *file,
				struct address_space *mapping,
				loff_t pos, unsigned len, unsigned flags,
				struct page **pagep, void **fsdata)
{
	struct inode *inode;
	struct page *page;
	pgoff_t index;
	int ret;
	int old_ref = 0;

 	inode = mapping->host;
	*fsdata = NULL;
 	if (flags & AOP_FLAG_CONT_EXPAND &&
 	    (pos & (inode->i_sb->s_blocksize - 1)) == 0) {
 		pos ++;
		*fsdata = (void *)(unsigned long)flags;
	}

	index = pos >> PAGE_SHIFT;
	page = grab_cache_page_write_begin(mapping, index, flags);
	if (!page)
		return -ENOMEM;
	*pagep = page;

	reiserfs_wait_on_write_block(inode->i_sb);
	fix_tail_page_for_writing(page);
	if (reiserfs_transaction_running(inode->i_sb)) {
		struct reiserfs_transaction_handle *th;
		th = (struct reiserfs_transaction_handle *)current->
		    journal_info;
		BUG_ON(!th->t_refcount);
		BUG_ON(!th->t_trans_id);
		old_ref = th->t_refcount;
		th->t_refcount++;
	}
	ret = __block_write_begin(page, pos, len, reiserfs_get_block);
	if (ret && reiserfs_transaction_running(inode->i_sb)) {
		struct reiserfs_transaction_handle *th = current->journal_info;
		/*
		 * this gets a little ugly.  If reiserfs_get_block returned an
		 * error and left a transacstion running, we've got to close
		 * it, and we've got to free handle if it was a persistent
		 * transaction.
		 *
		 * But, if we had nested into an existing transaction, we need
		 * to just drop the ref count on the handle.
		 *
		 * If old_ref == 0, the transaction is from reiserfs_get_block,
		 * and it was a persistent trans.  Otherwise, it was nested
		 * above.
		 */
		if (th->t_refcount > old_ref) {
			if (old_ref)
				th->t_refcount--;
			else {
				int err;
				reiserfs_write_lock(inode->i_sb);
				err = reiserfs_end_persistent_transaction(th);
				reiserfs_write_unlock(inode->i_sb);
				if (err)
					ret = err;
			}
		}
	}
	if (ret) {
		unlock_page(page);
		put_page(page);
		/* Truncate allocated blocks */
		reiserfs_truncate_failed_write(inode);
	}
	return ret;
}