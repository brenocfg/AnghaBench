#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int umode_t ;
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; } ;
struct dentry {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int EMLINK ; 
 int ENOSPC ; 
 int EXT4_DATA_TRANS_BLOCKS (int /*<<< orphan*/ ) ; 
 scalar_t__ EXT4_DIR_LINK_MAX (struct inode*) ; 
 int /*<<< orphan*/  EXT4_HT_DIR ; 
 int EXT4_INDEX_EXTRA_TRANS_BLOCKS ; 
 scalar_t__ IS_DIRSYNC (struct inode*) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int S_IFDIR ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 int /*<<< orphan*/  d_instantiate_new (struct dentry*,struct inode*) ; 
 int dquot_initialize (struct inode*) ; 
 int ext4_add_entry (int /*<<< orphan*/ *,struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  ext4_dir_inode_operations ; 
 int /*<<< orphan*/  ext4_dir_operations ; 
 int /*<<< orphan*/  ext4_handle_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_inc_count (int /*<<< orphan*/ *,struct inode*) ; 
 int ext4_init_new_dir (int /*<<< orphan*/ *,struct inode*,struct inode*) ; 
 int /*<<< orphan*/ * ext4_journal_current_handle () ; 
 int /*<<< orphan*/  ext4_journal_stop (int /*<<< orphan*/ *) ; 
 int ext4_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 
 struct inode* ext4_new_inode_start_handle (struct inode*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ext4_should_retry_alloc (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ext4_update_dx_flag (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

__attribute__((used)) static int ext4_mkdir(struct inode *dir, struct dentry *dentry, umode_t mode)
{
	handle_t *handle;
	struct inode *inode;
	int err, credits, retries = 0;

	if (EXT4_DIR_LINK_MAX(dir))
		return -EMLINK;

	err = dquot_initialize(dir);
	if (err)
		return err;

	credits = (EXT4_DATA_TRANS_BLOCKS(dir->i_sb) +
		   EXT4_INDEX_EXTRA_TRANS_BLOCKS + 3);
retry:
	inode = ext4_new_inode_start_handle(dir, S_IFDIR | mode,
					    &dentry->d_name,
					    0, NULL, EXT4_HT_DIR, credits);
	handle = ext4_journal_current_handle();
	err = PTR_ERR(inode);
	if (IS_ERR(inode))
		goto out_stop;

	inode->i_op = &ext4_dir_inode_operations;
	inode->i_fop = &ext4_dir_operations;
	err = ext4_init_new_dir(handle, dir, inode);
	if (err)
		goto out_clear_inode;
	err = ext4_mark_inode_dirty(handle, inode);
	if (!err)
		err = ext4_add_entry(handle, dentry, inode);
	if (err) {
out_clear_inode:
		clear_nlink(inode);
		unlock_new_inode(inode);
		ext4_mark_inode_dirty(handle, inode);
		iput(inode);
		goto out_stop;
	}
	ext4_inc_count(handle, dir);
	ext4_update_dx_flag(dir);
	err = ext4_mark_inode_dirty(handle, dir);
	if (err)
		goto out_clear_inode;
	d_instantiate_new(dentry, inode);
	if (IS_DIRSYNC(dir))
		ext4_handle_sync(handle);

out_stop:
	if (handle)
		ext4_journal_stop(handle);
	if (err == -ENOSPC && ext4_should_retry_alloc(dir->i_sb, &retries))
		goto retry;
	return err;
}