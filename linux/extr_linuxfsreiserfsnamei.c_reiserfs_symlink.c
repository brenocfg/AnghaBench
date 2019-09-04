#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct reiserfs_transaction_handle {int dummy; } ;
struct reiserfs_security_handle {int dummy; } ;
struct inode {TYPE_2__* i_sb; TYPE_1__* i_mapping; int /*<<< orphan*/ * i_op; } ;
struct TYPE_11__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_4__ d_name; } ;
struct TYPE_10__ {int /*<<< orphan*/  s_blocksize; } ;
struct TYPE_9__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int JOURNAL_PER_BALANCE_CNT ; 
 int MAX_DIRECT_ITEM_LEN (int /*<<< orphan*/ ) ; 
 int REISERFS_QUOTA_INIT_BLOCKS (TYPE_2__*) ; 
 int REISERFS_QUOTA_TRANS_BLOCKS (TYPE_2__*) ; 
 int ROUND_UP (int /*<<< orphan*/ ) ; 
 int S_IFLNK ; 
 int S_IRWXUGO ; 
 int /*<<< orphan*/  d_instantiate_new (struct dentry*,struct inode*) ; 
 int dquot_initialize (struct inode*) ; 
 int /*<<< orphan*/  drop_new_inode (struct inode*) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int /*<<< orphan*/  inode_nohighmem (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int journal_begin (struct reiserfs_transaction_handle*,TYPE_2__*,int) ; 
 int journal_end (struct reiserfs_transaction_handle*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int /*<<< orphan*/ ) ; 
 struct inode* new_inode (TYPE_2__*) ; 
 int new_inode_init (struct inode*,struct inode*,int) ; 
 int /*<<< orphan*/  padd_item (char*,int,int /*<<< orphan*/ ) ; 
 int reiserfs_add_entry (struct reiserfs_transaction_handle*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct inode*,int) ; 
 int /*<<< orphan*/  reiserfs_address_space_operations ; 
 int reiserfs_new_inode (struct reiserfs_transaction_handle*,struct inode*,int,char*,int /*<<< orphan*/ ,struct dentry*,struct inode*,struct reiserfs_security_handle*) ; 
 int reiserfs_security_init (struct inode*,struct inode*,TYPE_4__*,struct reiserfs_security_handle*) ; 
 int /*<<< orphan*/  reiserfs_symlink_inode_operations ; 
 int /*<<< orphan*/  reiserfs_update_inode_transaction (struct inode*) ; 
 int /*<<< orphan*/  reiserfs_update_sd (struct reiserfs_transaction_handle*,struct inode*) ; 
 int /*<<< orphan*/  reiserfs_write_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  reiserfs_write_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

__attribute__((used)) static int reiserfs_symlink(struct inode *parent_dir,
			    struct dentry *dentry, const char *symname)
{
	int retval;
	struct inode *inode;
	char *name;
	int item_len;
	struct reiserfs_transaction_handle th;
	struct reiserfs_security_handle security;
	int mode = S_IFLNK | S_IRWXUGO;
	/*
	 * We need blocks for transaction + (user+group)*(quotas for
	 * new inode + update of quota for directory owner)
	 */
	int jbegin_count =
	    JOURNAL_PER_BALANCE_CNT * 3 +
	    2 * (REISERFS_QUOTA_INIT_BLOCKS(parent_dir->i_sb) +
		 REISERFS_QUOTA_TRANS_BLOCKS(parent_dir->i_sb));

	retval = dquot_initialize(parent_dir);
	if (retval)
		return retval;

	if (!(inode = new_inode(parent_dir->i_sb))) {
		return -ENOMEM;
	}
	retval = new_inode_init(inode, parent_dir, mode);
	if (retval) {
		drop_new_inode(inode);
		return retval;
	}

	retval = reiserfs_security_init(parent_dir, inode, &dentry->d_name,
					&security);
	if (retval < 0) {
		drop_new_inode(inode);
		return retval;
	}
	jbegin_count += retval;

	reiserfs_write_lock(parent_dir->i_sb);
	item_len = ROUND_UP(strlen(symname));
	if (item_len > MAX_DIRECT_ITEM_LEN(parent_dir->i_sb->s_blocksize)) {
		retval = -ENAMETOOLONG;
		drop_new_inode(inode);
		goto out_failed;
	}

	name = kmalloc(item_len, GFP_NOFS);
	if (!name) {
		drop_new_inode(inode);
		retval = -ENOMEM;
		goto out_failed;
	}
	memcpy(name, symname, strlen(symname));
	padd_item(name, item_len, strlen(symname));

	retval = journal_begin(&th, parent_dir->i_sb, jbegin_count);
	if (retval) {
		drop_new_inode(inode);
		kfree(name);
		goto out_failed;
	}

	retval =
	    reiserfs_new_inode(&th, parent_dir, mode, name, strlen(symname),
			       dentry, inode, &security);
	kfree(name);
	if (retval) {		/* reiserfs_new_inode iputs for us */
		goto out_failed;
	}

	reiserfs_update_inode_transaction(inode);
	reiserfs_update_inode_transaction(parent_dir);

	inode->i_op = &reiserfs_symlink_inode_operations;
	inode_nohighmem(inode);
	inode->i_mapping->a_ops = &reiserfs_address_space_operations;

	retval = reiserfs_add_entry(&th, parent_dir, dentry->d_name.name,
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
	reiserfs_write_unlock(parent_dir->i_sb);
	return retval;
}