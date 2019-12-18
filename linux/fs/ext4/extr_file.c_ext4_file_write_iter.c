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
struct kiocb {int ki_flags; int* private; int /*<<< orphan*/  ki_pos; int /*<<< orphan*/  ki_filp; } ;
struct iov_iter {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  EIOCBQUEUED ; 
 int /*<<< orphan*/  EXT4_INODE_EXTENTS ; 
 int /*<<< orphan*/  EXT4_SB (int /*<<< orphan*/ ) ; 
 int IOCB_DIRECT ; 
 int IOCB_NOWAIT ; 
 scalar_t__ IS_DAX (struct inode*) ; 
 int /*<<< orphan*/  __generic_file_write_iter (struct kiocb*,struct iov_iter*) ; 
 int /*<<< orphan*/  ext4_dax_write_iter (struct kiocb*,struct iov_iter*) ; 
 int /*<<< orphan*/  ext4_forced_shutdown (int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_overwrite_io (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_should_dioread_nolock (struct inode*) ; 
 scalar_t__ ext4_test_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_unaligned_aio (struct inode*,struct iov_iter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_unwritten_wait (struct inode*) ; 
 int /*<<< orphan*/  ext4_write_checks (struct kiocb*,struct iov_iter*) ; 
 struct inode* file_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_write_sync (struct kiocb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_trylock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  iov_iter_count (struct iov_iter*) ; 
 int /*<<< orphan*/  is_sync_kiocb (struct kiocb*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
ext4_file_write_iter(struct kiocb *iocb, struct iov_iter *from)
{
	struct inode *inode = file_inode(iocb->ki_filp);
	int o_direct = iocb->ki_flags & IOCB_DIRECT;
	int unaligned_aio = 0;
	int overwrite = 0;
	ssize_t ret;

	if (unlikely(ext4_forced_shutdown(EXT4_SB(inode->i_sb))))
		return -EIO;

#ifdef CONFIG_FS_DAX
	if (IS_DAX(inode))
		return ext4_dax_write_iter(iocb, from);
#endif

	if (!inode_trylock(inode)) {
		if (iocb->ki_flags & IOCB_NOWAIT)
			return -EAGAIN;
		inode_lock(inode);
	}

	ret = ext4_write_checks(iocb, from);
	if (ret <= 0)
		goto out;

	/*
	 * Unaligned direct AIO must be serialized among each other as zeroing
	 * of partial blocks of two competing unaligned AIOs can result in data
	 * corruption.
	 */
	if (o_direct && ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS) &&
	    !is_sync_kiocb(iocb) &&
	    ext4_unaligned_aio(inode, from, iocb->ki_pos)) {
		unaligned_aio = 1;
		ext4_unwritten_wait(inode);
	}

	iocb->private = &overwrite;
	/* Check whether we do a DIO overwrite or not */
	if (o_direct && !unaligned_aio) {
		if (ext4_overwrite_io(inode, iocb->ki_pos, iov_iter_count(from))) {
			if (ext4_should_dioread_nolock(inode))
				overwrite = 1;
		} else if (iocb->ki_flags & IOCB_NOWAIT) {
			ret = -EAGAIN;
			goto out;
		}
	}

	ret = __generic_file_write_iter(iocb, from);
	/*
	 * Unaligned direct AIO must be the only IO in flight. Otherwise
	 * overlapping aligned IO after unaligned might result in data
	 * corruption.
	 */
	if (ret == -EIOCBQUEUED && unaligned_aio)
		ext4_unwritten_wait(inode);
	inode_unlock(inode);

	if (ret > 0)
		ret = generic_write_sync(iocb, ret);

	return ret;

out:
	inode_unlock(inode);
	return ret;
}