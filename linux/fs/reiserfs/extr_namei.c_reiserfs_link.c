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
struct reiserfs_transaction_handle {int dummy; } ;
struct inode {scalar_t__ i_nlink; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_ctime; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; } ;

/* Variables and functions */
 int EMLINK ; 
 int JOURNAL_PER_BALANCE_CNT ; 
 scalar_t__ REISERFS_LINK_MAX ; 
 int REISERFS_QUOTA_TRANS_BLOCKS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int dquot_initialize (struct inode*) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int /*<<< orphan*/  ihold (struct inode*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int journal_begin (struct reiserfs_transaction_handle*,int /*<<< orphan*/ ,int) ; 
 int journal_end (struct reiserfs_transaction_handle*) ; 
 int reiserfs_add_entry (struct reiserfs_transaction_handle*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct inode*,int) ; 
 int /*<<< orphan*/  reiserfs_update_inode_transaction (struct inode*) ; 
 int /*<<< orphan*/  reiserfs_update_sd (struct reiserfs_transaction_handle*,struct inode*) ; 
 int /*<<< orphan*/  reiserfs_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_write_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reiserfs_link(struct dentry *old_dentry, struct inode *dir,
			 struct dentry *dentry)
{
	int retval;
	struct inode *inode = d_inode(old_dentry);
	struct reiserfs_transaction_handle th;
	/*
	 * We need blocks for transaction + update of quotas for
	 * the owners of the directory
	 */
	int jbegin_count =
	    JOURNAL_PER_BALANCE_CNT * 3 +
	    2 * REISERFS_QUOTA_TRANS_BLOCKS(dir->i_sb);

	retval = dquot_initialize(dir);
	if (retval)
		return retval;

	reiserfs_write_lock(dir->i_sb);
	if (inode->i_nlink >= REISERFS_LINK_MAX) {
		/* FIXME: sd_nlink is 32 bit for new files */
		reiserfs_write_unlock(dir->i_sb);
		return -EMLINK;
	}

	/* inc before scheduling so reiserfs_unlink knows we are here */
	inc_nlink(inode);

	retval = journal_begin(&th, dir->i_sb, jbegin_count);
	if (retval) {
		drop_nlink(inode);
		reiserfs_write_unlock(dir->i_sb);
		return retval;
	}

	/* create new entry */
	retval =
	    reiserfs_add_entry(&th, dir, dentry->d_name.name,
			       dentry->d_name.len, inode, 1 /*visible */ );

	reiserfs_update_inode_transaction(inode);
	reiserfs_update_inode_transaction(dir);

	if (retval) {
		int err;
		drop_nlink(inode);
		err = journal_end(&th);
		reiserfs_write_unlock(dir->i_sb);
		return err ? err : retval;
	}

	inode->i_ctime = current_time(inode);
	reiserfs_update_sd(&th, inode);

	ihold(inode);
	d_instantiate(dentry, inode);
	retval = journal_end(&th);
	reiserfs_write_unlock(dir->i_sb);
	return retval;
}