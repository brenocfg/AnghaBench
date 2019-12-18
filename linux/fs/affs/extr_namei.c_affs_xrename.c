#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct dentry {int dummy; } ;
struct buffer_head {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_ino; } ;

/* Variables and functions */
 TYPE_2__* AFFS_TAIL (struct super_block*,struct buffer_head*) ; 
 int EIO ; 
 struct buffer_head* affs_bread (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  affs_brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  affs_copy_name (int /*<<< orphan*/ ,struct dentry*) ; 
 int /*<<< orphan*/  affs_fix_checksum (struct super_block*,struct buffer_head*) ; 
 int affs_insert_hash (struct inode*,struct buffer_head*) ; 
 int /*<<< orphan*/  affs_lock_dir (struct inode*) ; 
 int affs_remove_hash (struct inode*,struct buffer_head*) ; 
 int /*<<< orphan*/  affs_unlock_dir (struct inode*) ; 
 TYPE_1__* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  mark_buffer_dirty_inode (struct buffer_head*,struct inode*) ; 

__attribute__((used)) static int
affs_xrename(struct inode *old_dir, struct dentry *old_dentry,
	     struct inode *new_dir, struct dentry *new_dentry)
{

	struct super_block *sb = old_dir->i_sb;
	struct buffer_head *bh_old = NULL;
	struct buffer_head *bh_new = NULL;
	int retval;

	bh_old = affs_bread(sb, d_inode(old_dentry)->i_ino);
	if (!bh_old)
		return -EIO;

	bh_new = affs_bread(sb, d_inode(new_dentry)->i_ino);
	if (!bh_new)
		return -EIO;

	/* Remove old header from its parent directory. */
	affs_lock_dir(old_dir);
	retval = affs_remove_hash(old_dir, bh_old);
	affs_unlock_dir(old_dir);
	if (retval)
		goto done;

	/* Remove new header from its parent directory. */
	affs_lock_dir(new_dir);
	retval = affs_remove_hash(new_dir, bh_new);
	affs_unlock_dir(new_dir);
	if (retval)
		goto done;

	/* Insert old into the new directory with the new name. */
	affs_copy_name(AFFS_TAIL(sb, bh_old)->name, new_dentry);
	affs_fix_checksum(sb, bh_old);
	affs_lock_dir(new_dir);
	retval = affs_insert_hash(new_dir, bh_old);
	affs_unlock_dir(new_dir);

	/* Insert new into the old directory with the old name. */
	affs_copy_name(AFFS_TAIL(sb, bh_new)->name, old_dentry);
	affs_fix_checksum(sb, bh_new);
	affs_lock_dir(old_dir);
	retval = affs_insert_hash(old_dir, bh_new);
	affs_unlock_dir(old_dir);
done:
	mark_buffer_dirty_inode(bh_old, new_dir);
	mark_buffer_dirty_inode(bh_new, old_dir);
	affs_brelse(bh_old);
	affs_brelse(bh_new);
	return retval;
}