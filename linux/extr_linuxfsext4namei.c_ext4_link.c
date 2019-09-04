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
struct inode {int i_nlink; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_ctime; } ;
struct dentry {struct inode* d_inode; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_projid; } ;

/* Variables and functions */
 int EMLINK ; 
 int ENOSPC ; 
 int EXDEV ; 
 scalar_t__ EXT4_DATA_TRANS_BLOCKS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT4_HT_DIR ; 
 TYPE_1__* EXT4_I (struct inode*) ; 
 scalar_t__ EXT4_INDEX_EXTRA_TRANS_BLOCKS ; 
 int /*<<< orphan*/  EXT4_INODE_PROJINHERIT ; 
 int EXT4_LINK_MAX ; 
 scalar_t__ IS_DIRSYNC (struct inode*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int dquot_initialize (struct inode*) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int ext4_add_entry (int /*<<< orphan*/ *,struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  ext4_handle_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_inc_count (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/ * ext4_journal_start (struct inode*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ext4_journal_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_orphan_del (int /*<<< orphan*/ *,struct inode*) ; 
 scalar_t__ ext4_should_retry_alloc (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ ext4_test_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int fscrypt_prepare_link (struct dentry*,struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  ihold (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  projid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_link(struct dentry *old_dentry,
		     struct inode *dir, struct dentry *dentry)
{
	handle_t *handle;
	struct inode *inode = d_inode(old_dentry);
	int err, retries = 0;

	if (inode->i_nlink >= EXT4_LINK_MAX)
		return -EMLINK;

	err = fscrypt_prepare_link(old_dentry, dir, dentry);
	if (err)
		return err;

	if ((ext4_test_inode_flag(dir, EXT4_INODE_PROJINHERIT)) &&
	    (!projid_eq(EXT4_I(dir)->i_projid,
			EXT4_I(old_dentry->d_inode)->i_projid)))
		return -EXDEV;

	err = dquot_initialize(dir);
	if (err)
		return err;

retry:
	handle = ext4_journal_start(dir, EXT4_HT_DIR,
		(EXT4_DATA_TRANS_BLOCKS(dir->i_sb) +
		 EXT4_INDEX_EXTRA_TRANS_BLOCKS) + 1);
	if (IS_ERR(handle))
		return PTR_ERR(handle);

	if (IS_DIRSYNC(dir))
		ext4_handle_sync(handle);

	inode->i_ctime = current_time(inode);
	ext4_inc_count(handle, inode);
	ihold(inode);

	err = ext4_add_entry(handle, dentry, inode);
	if (!err) {
		ext4_mark_inode_dirty(handle, inode);
		/* this can happen only for tmpfile being
		 * linked the first time
		 */
		if (inode->i_nlink == 1)
			ext4_orphan_del(handle, inode);
		d_instantiate(dentry, inode);
	} else {
		drop_nlink(inode);
		iput(inode);
	}
	ext4_journal_stop(handle);
	if (err == -ENOSPC && ext4_should_retry_alloc(dir->i_sb, &retries))
		goto retry;
	return err;
}