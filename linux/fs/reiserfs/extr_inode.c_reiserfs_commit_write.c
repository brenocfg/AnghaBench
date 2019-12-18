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
struct reiserfs_transaction_handle {int dummy; } ;
struct page {scalar_t__ index; TYPE_1__* mapping; } ;
struct inode {scalar_t__ i_size; int /*<<< orphan*/  i_sb; } ;
struct file {int dummy; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_6__ {int /*<<< orphan*/  i_flags; } ;
struct TYPE_5__ {struct reiserfs_transaction_handle* journal_info; } ;
struct TYPE_4__ {struct inode* host; } ;

/* Variables and functions */
 scalar_t__ PAGE_SHIFT ; 
 TYPE_3__* REISERFS_I (struct inode*) ; 
 TYPE_2__* current ; 
 scalar_t__ have_large_tails (int /*<<< orphan*/ ) ; 
 scalar_t__ have_small_tails (int /*<<< orphan*/ ) ; 
 int i_block_size (struct inode*) ; 
 int /*<<< orphan*/  i_pack_on_close_mask ; 
 int journal_begin (struct reiserfs_transaction_handle*,int /*<<< orphan*/ ,int) ; 
 int journal_end (struct reiserfs_transaction_handle*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  reiserfs_commit_page (struct inode*,struct page*,unsigned int,unsigned int) ; 
 int reiserfs_end_persistent_transaction (struct reiserfs_transaction_handle*) ; 
 scalar_t__ reiserfs_transaction_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_update_inode_transaction (struct inode*) ; 
 int /*<<< orphan*/  reiserfs_update_sd (struct reiserfs_transaction_handle*,struct inode*) ; 
 int /*<<< orphan*/  reiserfs_wait_on_write_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_write_lock_nested (int /*<<< orphan*/ ,int) ; 
 int reiserfs_write_unlock_nested (int /*<<< orphan*/ ) ; 

int reiserfs_commit_write(struct file *f, struct page *page,
			  unsigned from, unsigned to)
{
	struct inode *inode = page->mapping->host;
	loff_t pos = ((loff_t) page->index << PAGE_SHIFT) + to;
	int ret = 0;
	int update_sd = 0;
	struct reiserfs_transaction_handle *th = NULL;
	int depth;

	depth = reiserfs_write_unlock_nested(inode->i_sb);
	reiserfs_wait_on_write_block(inode->i_sb);
	reiserfs_write_lock_nested(inode->i_sb, depth);

	if (reiserfs_transaction_running(inode->i_sb)) {
		th = current->journal_info;
	}
	reiserfs_commit_page(inode, page, from, to);

	/*
	 * generic_commit_write does this for us, but does not update the
	 * transaction tracking stuff when the size changes.  So, we have
	 * to do the i_size updates here.
	 */
	if (pos > inode->i_size) {
		struct reiserfs_transaction_handle myth;
		/*
		 * If the file have grown beyond the border where it
		 * can have a tail, unmark it as needing a tail
		 * packing
		 */
		if ((have_large_tails(inode->i_sb)
		     && inode->i_size > i_block_size(inode) * 4)
		    || (have_small_tails(inode->i_sb)
			&& inode->i_size > i_block_size(inode)))
			REISERFS_I(inode)->i_flags &= ~i_pack_on_close_mask;

		ret = journal_begin(&myth, inode->i_sb, 1);
		if (ret)
			goto journal_error;

		reiserfs_update_inode_transaction(inode);
		inode->i_size = pos;
		/*
		 * this will just nest into our transaction.  It's important
		 * to use mark_inode_dirty so the inode gets pushed around
		 * on the dirty lists, and so that O_SYNC works as expected
		 */
		mark_inode_dirty(inode);
		reiserfs_update_sd(&myth, inode);
		update_sd = 1;
		ret = journal_end(&myth);
		if (ret)
			goto journal_error;
	}
	if (th) {
		if (!update_sd)
			mark_inode_dirty(inode);
		ret = reiserfs_end_persistent_transaction(th);
		if (ret)
			goto out;
	}

out:
	return ret;

journal_error:
	if (th) {
		if (!update_sd)
			reiserfs_update_sd(th, inode);
		ret = reiserfs_end_persistent_transaction(th);
	}

	return ret;
}