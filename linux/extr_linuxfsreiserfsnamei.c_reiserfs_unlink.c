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
struct reiserfs_dir_entry {scalar_t__ de_objectid; scalar_t__ de_entrylen; int /*<<< orphan*/  de_entry_key; int /*<<< orphan*/ * de_gen_number_bit_string; } ;
struct inode {scalar_t__ i_ino; unsigned long i_nlink; int /*<<< orphan*/  i_sb; void* i_mtime; void* i_ctime; int /*<<< orphan*/  i_size; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; } ;

/* Variables and functions */
 scalar_t__ DEH_SIZE ; 
 int EIO ; 
 int ENOENT ; 
 int /*<<< orphan*/  INITIALIZE_PATH (int /*<<< orphan*/ ) ; 
 int IO_ERROR ; 
 int JOURNAL_PER_BALANCE_CNT ; 
 int NAME_NOT_FOUND ; 
 int REISERFS_QUOTA_TRANS_BLOCKS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_save_link (struct reiserfs_transaction_handle*,struct inode*,int /*<<< orphan*/ ) ; 
 void* current_time (struct inode*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int dquot_initialize (struct inode*) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int journal_begin (struct reiserfs_transaction_handle*,int /*<<< orphan*/ ,int) ; 
 int journal_end (struct reiserfs_transaction_handle*) ; 
 int /*<<< orphan*/  path ; 
 int /*<<< orphan*/  pathrelse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reiserfs_check_path (int /*<<< orphan*/ *) ; 
 int reiserfs_cut_from_item (struct reiserfs_transaction_handle*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int reiserfs_find_entry (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct reiserfs_dir_entry*) ; 
 int /*<<< orphan*/  reiserfs_update_inode_transaction (struct inode*) ; 
 int /*<<< orphan*/  reiserfs_update_sd (struct reiserfs_transaction_handle*,struct inode*) ; 
 int /*<<< orphan*/  reiserfs_warning (int /*<<< orphan*/ ,char*,char*,scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  reiserfs_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_write_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int) ; 

__attribute__((used)) static int reiserfs_unlink(struct inode *dir, struct dentry *dentry)
{
	int retval, err;
	struct inode *inode;
	struct reiserfs_dir_entry de;
	INITIALIZE_PATH(path);
	struct reiserfs_transaction_handle th;
	int jbegin_count;
	unsigned long savelink;

	retval = dquot_initialize(dir);
	if (retval)
		return retval;

	inode = d_inode(dentry);

	/*
	 * in this transaction we can be doing at max two balancings and
	 * update two stat datas, we change quotas of the owner of the
	 * directory and of the owner of the parent directory. The quota
	 * structure is possibly deleted only on iput => outside of
	 * this transaction
	 */
	jbegin_count =
	    JOURNAL_PER_BALANCE_CNT * 2 + 2 +
	    4 * REISERFS_QUOTA_TRANS_BLOCKS(dir->i_sb);

	reiserfs_write_lock(dir->i_sb);
	retval = journal_begin(&th, dir->i_sb, jbegin_count);
	if (retval)
		goto out_unlink;

	de.de_gen_number_bit_string = NULL;
	if ((retval =
	     reiserfs_find_entry(dir, dentry->d_name.name, dentry->d_name.len,
				 &path, &de)) == NAME_NOT_FOUND) {
		retval = -ENOENT;
		goto end_unlink;
	} else if (retval == IO_ERROR) {
		retval = -EIO;
		goto end_unlink;
	}

	reiserfs_update_inode_transaction(inode);
	reiserfs_update_inode_transaction(dir);

	if (de.de_objectid != inode->i_ino) {
		/*
		 * FIXME: compare key of an object and a key found in the entry
		 */
		retval = -EIO;
		goto end_unlink;
	}

	if (!inode->i_nlink) {
		reiserfs_warning(inode->i_sb, "reiserfs-7042",
				 "deleting nonexistent file (%lu), %d",
				 inode->i_ino, inode->i_nlink);
		set_nlink(inode, 1);
	}

	drop_nlink(inode);

	/*
	 * we schedule before doing the add_save_link call, save the link
	 * count so we don't race
	 */
	savelink = inode->i_nlink;

	retval =
	    reiserfs_cut_from_item(&th, &path, &de.de_entry_key, dir, NULL,
				   0);
	if (retval < 0) {
		inc_nlink(inode);
		goto end_unlink;
	}
	inode->i_ctime = current_time(inode);
	reiserfs_update_sd(&th, inode);

	dir->i_size -= (de.de_entrylen + DEH_SIZE);
	dir->i_ctime = dir->i_mtime = current_time(dir);
	reiserfs_update_sd(&th, dir);

	if (!savelink)
		/* prevent file from getting lost */
		add_save_link(&th, inode, 0 /* not truncate */ );

	retval = journal_end(&th);
	reiserfs_check_path(&path);
	reiserfs_write_unlock(dir->i_sb);
	return retval;

end_unlink:
	pathrelse(&path);
	err = journal_end(&th);
	reiserfs_check_path(&path);
	if (err)
		retval = err;
out_unlink:
	reiserfs_write_unlock(dir->i_sb);
	return retval;
}