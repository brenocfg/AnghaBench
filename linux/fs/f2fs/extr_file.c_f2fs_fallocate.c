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
struct inode {scalar_t__ i_size; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_mode; } ;
struct file {int dummy; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 long EINVAL ; 
 long EIO ; 
 long ENOSPC ; 
 long EOPNOTSUPP ; 
 int /*<<< orphan*/  F2FS_I_SB (struct inode*) ; 
 int FALLOC_FL_COLLAPSE_RANGE ; 
 int FALLOC_FL_INSERT_RANGE ; 
 int FALLOC_FL_KEEP_SIZE ; 
 int FALLOC_FL_PUNCH_HOLE ; 
 int FALLOC_FL_ZERO_RANGE ; 
 scalar_t__ IS_ENCRYPTED (struct inode*) ; 
 int /*<<< orphan*/  REQ_TIME ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 long expand_inode_data (struct inode*,scalar_t__,scalar_t__,int) ; 
 long f2fs_collapse_range (struct inode*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  f2fs_cp_error (int /*<<< orphan*/ ) ; 
 long f2fs_insert_range (struct inode*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  f2fs_is_checkpoint_ready (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_mark_inode_dirty_sync (struct inode*,int) ; 
 int /*<<< orphan*/  f2fs_update_time (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long f2fs_zero_range (struct inode*,scalar_t__,scalar_t__,int) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 long punch_hole (struct inode*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  trace_f2fs_fallocate (struct inode*,int,scalar_t__,scalar_t__,long) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static long f2fs_fallocate(struct file *file, int mode,
				loff_t offset, loff_t len)
{
	struct inode *inode = file_inode(file);
	long ret = 0;

	if (unlikely(f2fs_cp_error(F2FS_I_SB(inode))))
		return -EIO;
	if (!f2fs_is_checkpoint_ready(F2FS_I_SB(inode)))
		return -ENOSPC;

	/* f2fs only support ->fallocate for regular file */
	if (!S_ISREG(inode->i_mode))
		return -EINVAL;

	if (IS_ENCRYPTED(inode) &&
		(mode & (FALLOC_FL_COLLAPSE_RANGE | FALLOC_FL_INSERT_RANGE)))
		return -EOPNOTSUPP;

	if (mode & ~(FALLOC_FL_KEEP_SIZE | FALLOC_FL_PUNCH_HOLE |
			FALLOC_FL_COLLAPSE_RANGE | FALLOC_FL_ZERO_RANGE |
			FALLOC_FL_INSERT_RANGE))
		return -EOPNOTSUPP;

	inode_lock(inode);

	if (mode & FALLOC_FL_PUNCH_HOLE) {
		if (offset >= inode->i_size)
			goto out;

		ret = punch_hole(inode, offset, len);
	} else if (mode & FALLOC_FL_COLLAPSE_RANGE) {
		ret = f2fs_collapse_range(inode, offset, len);
	} else if (mode & FALLOC_FL_ZERO_RANGE) {
		ret = f2fs_zero_range(inode, offset, len, mode);
	} else if (mode & FALLOC_FL_INSERT_RANGE) {
		ret = f2fs_insert_range(inode, offset, len);
	} else {
		ret = expand_inode_data(inode, offset, len, mode);
	}

	if (!ret) {
		inode->i_mtime = inode->i_ctime = current_time(inode);
		f2fs_mark_inode_dirty_sync(inode, false);
		f2fs_update_time(F2FS_I_SB(inode), REQ_TIME);
	}

out:
	inode_unlock(inode);

	trace_f2fs_fallocate(inode, mode, offset, len, ret);
	return ret;
}