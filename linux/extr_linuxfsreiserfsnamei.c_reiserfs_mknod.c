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
typedef  int /*<<< orphan*/  umode_t ;
struct reiserfs_transaction_handle {int dummy; } ;
struct reiserfs_security_handle {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; int /*<<< orphan*/ * i_op; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int ENOMEM ; 
 int JOURNAL_PER_BALANCE_CNT ; 
 int REISERFS_QUOTA_INIT_BLOCKS (int /*<<< orphan*/ ) ; 
 int REISERFS_QUOTA_TRANS_BLOCKS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_instantiate_new (struct dentry*,struct inode*) ; 
 int dquot_initialize (struct inode*) ; 
 int /*<<< orphan*/  drop_new_inode (struct inode*) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int journal_begin (struct reiserfs_transaction_handle*,int /*<<< orphan*/ ,int) ; 
 int journal_end (struct reiserfs_transaction_handle*) ; 
 struct inode* new_inode (int /*<<< orphan*/ ) ; 
 int new_inode_init (struct inode*,struct inode*,int /*<<< orphan*/ ) ; 
 int reiserfs_add_entry (struct reiserfs_transaction_handle*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct inode*,int) ; 
 scalar_t__ reiserfs_cache_default_acl (struct inode*) ; 
 int reiserfs_new_inode (struct reiserfs_transaction_handle*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct dentry*,struct inode*,struct reiserfs_security_handle*) ; 
 int reiserfs_security_init (struct inode*,struct inode*,TYPE_1__*,struct reiserfs_security_handle*) ; 
 int /*<<< orphan*/  reiserfs_special_inode_operations ; 
 int /*<<< orphan*/  reiserfs_update_inode_transaction (struct inode*) ; 
 int /*<<< orphan*/  reiserfs_update_sd (struct reiserfs_transaction_handle*,struct inode*) ; 
 int /*<<< orphan*/  reiserfs_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_write_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

__attribute__((used)) static int reiserfs_mknod(struct inode *dir, struct dentry *dentry, umode_t mode,
			  dev_t rdev)
{
	int retval;
	struct inode *inode;
	struct reiserfs_transaction_handle th;
	struct reiserfs_security_handle security;
	/*
	 * We need blocks for transaction + (user+group)*(quotas
	 * for new inode + update of quota for directory owner)
	 */
	int jbegin_count =
	    JOURNAL_PER_BALANCE_CNT * 3 +
	    2 * (REISERFS_QUOTA_INIT_BLOCKS(dir->i_sb) +
		 REISERFS_QUOTA_TRANS_BLOCKS(dir->i_sb));

	retval = dquot_initialize(dir);
	if (retval)
		return retval;

	if (!(inode = new_inode(dir->i_sb))) {
		return -ENOMEM;
	}
	retval = new_inode_init(inode, dir, mode);
	if (retval) {
		drop_new_inode(inode);
		return retval;
	}

	jbegin_count += reiserfs_cache_default_acl(dir);
	retval = reiserfs_security_init(dir, inode, &dentry->d_name, &security);
	if (retval < 0) {
		drop_new_inode(inode);
		return retval;
	}
	jbegin_count += retval;
	reiserfs_write_lock(dir->i_sb);

	retval = journal_begin(&th, dir->i_sb, jbegin_count);
	if (retval) {
		drop_new_inode(inode);
		goto out_failed;
	}

	retval =
	    reiserfs_new_inode(&th, dir, mode, NULL, 0 /*i_size */ , dentry,
			       inode, &security);
	if (retval) {
		goto out_failed;
	}

	inode->i_op = &reiserfs_special_inode_operations;
	init_special_inode(inode, inode->i_mode, rdev);

	/* FIXME: needed for block and char devices only */
	reiserfs_update_sd(&th, inode);

	reiserfs_update_inode_transaction(inode);
	reiserfs_update_inode_transaction(dir);

	retval =
	    reiserfs_add_entry(&th, dir, dentry->d_name.name,
			       dentry->d_name.len, inode, 1 /*visible */ );
	if (retval) {
		int err;
		drop_nlink(inode);
		reiserfs_update_sd(&th, inode);
		err = journal_end(&th);
		if (err)
			retval = err;
		unlock_new_inode(inode);
		iput(inode);
		goto out_failed;
	}

	d_instantiate_new(dentry, inode);
	retval = journal_end(&th);

out_failed:
	reiserfs_write_unlock(dir->i_sb);
	return retval;
}