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
struct kiocb {int ki_flags; size_t ki_pos; struct file* ki_filp; } ;
struct iov_iter {int dummy; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  APP_WRITE_IO ; 
 scalar_t__ EAGAIN ; 
 scalar_t__ EINVAL ; 
 scalar_t__ EIO ; 
 int /*<<< orphan*/  F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  FI_NO_PREALLOC ; 
 int IOCB_DIRECT ; 
 int IOCB_NOWAIT ; 
 int /*<<< orphan*/  WRITE ; 
 scalar_t__ __generic_file_write_iter (struct kiocb*,struct iov_iter*) ; 
 int /*<<< orphan*/  clear_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_cp_error (int /*<<< orphan*/ ) ; 
 scalar_t__ f2fs_force_buffered_io (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ f2fs_has_inline_data (struct inode*) ; 
 int /*<<< orphan*/  f2fs_overwrite_io (struct inode*,size_t,size_t) ; 
 int f2fs_preallocate_blocks (struct kiocb*,struct iov_iter*) ; 
 int /*<<< orphan*/  f2fs_truncate (struct inode*) ; 
 int /*<<< orphan*/  f2fs_update_iostat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct inode* file_inode (struct file*) ; 
 scalar_t__ generic_write_checks (struct kiocb*,struct iov_iter*) ; 
 scalar_t__ generic_write_sync (struct kiocb*,scalar_t__) ; 
 size_t i_size_read (struct inode*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_trylock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 size_t iov_iter_count (struct iov_iter*) ; 
 scalar_t__ iov_iter_fault_in_readable (struct iov_iter*,size_t) ; 
 int /*<<< orphan*/  set_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t f2fs_file_write_iter(struct kiocb *iocb, struct iov_iter *from)
{
	struct file *file = iocb->ki_filp;
	struct inode *inode = file_inode(file);
	ssize_t ret;

	if (unlikely(f2fs_cp_error(F2FS_I_SB(inode))))
		return -EIO;

	if ((iocb->ki_flags & IOCB_NOWAIT) && !(iocb->ki_flags & IOCB_DIRECT))
		return -EINVAL;

	if (!inode_trylock(inode)) {
		if (iocb->ki_flags & IOCB_NOWAIT)
			return -EAGAIN;
		inode_lock(inode);
	}

	ret = generic_write_checks(iocb, from);
	if (ret > 0) {
		bool preallocated = false;
		size_t target_size = 0;
		int err;

		if (iov_iter_fault_in_readable(from, iov_iter_count(from)))
			set_inode_flag(inode, FI_NO_PREALLOC);

		if ((iocb->ki_flags & IOCB_NOWAIT) &&
			(iocb->ki_flags & IOCB_DIRECT)) {
				if (!f2fs_overwrite_io(inode, iocb->ki_pos,
						iov_iter_count(from)) ||
					f2fs_has_inline_data(inode) ||
					f2fs_force_buffered_io(inode, WRITE)) {
						clear_inode_flag(inode,
								FI_NO_PREALLOC);
						inode_unlock(inode);
						return -EAGAIN;
				}

		} else {
			preallocated = true;
			target_size = iocb->ki_pos + iov_iter_count(from);

			err = f2fs_preallocate_blocks(iocb, from);
			if (err) {
				clear_inode_flag(inode, FI_NO_PREALLOC);
				inode_unlock(inode);
				return err;
			}
		}
		ret = __generic_file_write_iter(iocb, from);
		clear_inode_flag(inode, FI_NO_PREALLOC);

		/* if we couldn't write data, we should deallocate blocks. */
		if (preallocated && i_size_read(inode) < target_size)
			f2fs_truncate(inode);

		if (ret > 0)
			f2fs_update_iostat(F2FS_I_SB(inode), APP_WRITE_IO, ret);
	}
	inode_unlock(inode);

	if (ret > 0)
		ret = generic_write_sync(iocb, ret);
	return ret;
}