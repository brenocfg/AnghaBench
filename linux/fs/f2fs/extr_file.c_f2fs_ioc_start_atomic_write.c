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
struct inode {int /*<<< orphan*/  i_mapping; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_mode; } ;
struct file {int f_flags; } ;
struct f2fs_sb_info {int /*<<< orphan*/ * inode_lock; int /*<<< orphan*/ * inode_list; } ;
struct f2fs_inode_info {int /*<<< orphan*/  inmem_task; int /*<<< orphan*/ * i_gc_rwsem; int /*<<< orphan*/  inmem_ilist; } ;

/* Variables and functions */
 size_t ATOMIC_FILE ; 
 int EACCES ; 
 int EINVAL ; 
 struct f2fs_inode_info* F2FS_I (struct inode*) ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  FI_ATOMIC_FILE ; 
 int /*<<< orphan*/  FI_ATOMIC_REVOKE_REQUEST ; 
 int /*<<< orphan*/  LLONG_MAX ; 
 int O_DIRECT ; 
 int /*<<< orphan*/  REQ_TIME ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 size_t WRITE ; 
 int /*<<< orphan*/  clear_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int f2fs_convert_inline_inode (struct inode*) ; 
 scalar_t__ f2fs_is_atomic_file (struct inode*) ; 
 int /*<<< orphan*/  f2fs_update_time (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_warn (struct f2fs_sb_info*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct inode* file_inode (struct file*) ; 
 int filemap_write_and_wait_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_dirty_pages (struct inode*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_owner_or_capable (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 scalar_t__ is_inode_flag_set (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mnt_drop_write_file (struct file*) ; 
 int mnt_want_write_file (struct file*) ; 
 int /*<<< orphan*/  set_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stat_inc_atomic_write (struct inode*) ; 
 int /*<<< orphan*/  stat_update_max_atomic_write (struct inode*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int f2fs_ioc_start_atomic_write(struct file *filp)
{
	struct inode *inode = file_inode(filp);
	struct f2fs_inode_info *fi = F2FS_I(inode);
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	int ret;

	if (!inode_owner_or_capable(inode))
		return -EACCES;

	if (!S_ISREG(inode->i_mode))
		return -EINVAL;

	if (filp->f_flags & O_DIRECT)
		return -EINVAL;

	ret = mnt_want_write_file(filp);
	if (ret)
		return ret;

	inode_lock(inode);

	if (f2fs_is_atomic_file(inode)) {
		if (is_inode_flag_set(inode, FI_ATOMIC_REVOKE_REQUEST))
			ret = -EINVAL;
		goto out;
	}

	ret = f2fs_convert_inline_inode(inode);
	if (ret)
		goto out;

	down_write(&F2FS_I(inode)->i_gc_rwsem[WRITE]);

	/*
	 * Should wait end_io to count F2FS_WB_CP_DATA correctly by
	 * f2fs_is_atomic_file.
	 */
	if (get_dirty_pages(inode))
		f2fs_warn(F2FS_I_SB(inode), "Unexpected flush for atomic writes: ino=%lu, npages=%u",
			  inode->i_ino, get_dirty_pages(inode));
	ret = filemap_write_and_wait_range(inode->i_mapping, 0, LLONG_MAX);
	if (ret) {
		up_write(&F2FS_I(inode)->i_gc_rwsem[WRITE]);
		goto out;
	}

	spin_lock(&sbi->inode_lock[ATOMIC_FILE]);
	if (list_empty(&fi->inmem_ilist))
		list_add_tail(&fi->inmem_ilist, &sbi->inode_list[ATOMIC_FILE]);
	spin_unlock(&sbi->inode_lock[ATOMIC_FILE]);

	/* add inode in inmem_list first and set atomic_file */
	set_inode_flag(inode, FI_ATOMIC_FILE);
	clear_inode_flag(inode, FI_ATOMIC_REVOKE_REQUEST);
	up_write(&F2FS_I(inode)->i_gc_rwsem[WRITE]);

	f2fs_update_time(F2FS_I_SB(inode), REQ_TIME);
	F2FS_I(inode)->inmem_task = current;
	stat_inc_atomic_write(inode);
	stat_update_max_atomic_write(inode);
out:
	inode_unlock(inode);
	mnt_drop_write_file(filp);
	return ret;
}