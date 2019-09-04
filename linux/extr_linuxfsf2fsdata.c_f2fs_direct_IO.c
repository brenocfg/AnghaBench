#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct kiocb {int ki_hint; int ki_flags; scalar_t__ ki_pos; TYPE_1__* ki_filp; } ;
struct iov_iter {int dummy; } ;
struct inode {int dummy; } ;
struct f2fs_sb_info {int dummy; } ;
struct address_space {struct inode* host; } ;
typedef  int ssize_t ;
typedef  scalar_t__ loff_t ;
typedef  enum rw_hint { ____Placeholder_rw_hint } rw_hint ;
struct TYPE_6__ {int /*<<< orphan*/ * i_gc_rwsem; } ;
struct TYPE_5__ {int whint_mode; } ;
struct TYPE_4__ {struct address_space* f_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  APP_DIRECT_IO ; 
 int EAGAIN ; 
 TYPE_3__* F2FS_I (struct inode*) ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 TYPE_2__ F2FS_OPTION (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  FI_UPDATE_WRITE ; 
 int IOCB_NOWAIT ; 
 int WHINT_MODE_OFF ; 
 int WRITE ; 
 int WRITE_LIFE_NOT_SET ; 
 int blockdev_direct_IO (struct kiocb*,struct inode*,struct iov_iter*,int /*<<< orphan*/ ) ; 
 int check_direct_IO (struct inode*,struct iov_iter*,scalar_t__) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_read_trylock (int /*<<< orphan*/ *) ; 
 scalar_t__ f2fs_force_buffered_io (struct inode*,int) ; 
 int /*<<< orphan*/  f2fs_update_iostat (struct f2fs_sb_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  f2fs_write_failed (struct address_space*,scalar_t__) ; 
 int /*<<< orphan*/  get_data_block_dio ; 
 size_t iov_iter_count (struct iov_iter*) ; 
 int iov_iter_rw (struct iov_iter*) ; 
 int /*<<< orphan*/  set_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_f2fs_direct_IO_enter (struct inode*,scalar_t__,size_t,int) ; 
 int /*<<< orphan*/  trace_f2fs_direct_IO_exit (struct inode*,scalar_t__,size_t,int,int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t f2fs_direct_IO(struct kiocb *iocb, struct iov_iter *iter)
{
	struct address_space *mapping = iocb->ki_filp->f_mapping;
	struct inode *inode = mapping->host;
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	size_t count = iov_iter_count(iter);
	loff_t offset = iocb->ki_pos;
	int rw = iov_iter_rw(iter);
	int err;
	enum rw_hint hint = iocb->ki_hint;
	int whint_mode = F2FS_OPTION(sbi).whint_mode;

	err = check_direct_IO(inode, iter, offset);
	if (err)
		return err < 0 ? err : 0;

	if (f2fs_force_buffered_io(inode, rw))
		return 0;

	trace_f2fs_direct_IO_enter(inode, offset, count, rw);

	if (rw == WRITE && whint_mode == WHINT_MODE_OFF)
		iocb->ki_hint = WRITE_LIFE_NOT_SET;

	if (!down_read_trylock(&F2FS_I(inode)->i_gc_rwsem[rw])) {
		if (iocb->ki_flags & IOCB_NOWAIT) {
			iocb->ki_hint = hint;
			err = -EAGAIN;
			goto out;
		}
		down_read(&F2FS_I(inode)->i_gc_rwsem[rw]);
	}

	err = blockdev_direct_IO(iocb, inode, iter, get_data_block_dio);
	up_read(&F2FS_I(inode)->i_gc_rwsem[rw]);

	if (rw == WRITE) {
		if (whint_mode == WHINT_MODE_OFF)
			iocb->ki_hint = hint;
		if (err > 0) {
			f2fs_update_iostat(F2FS_I_SB(inode), APP_DIRECT_IO,
									err);
			set_inode_flag(inode, FI_UPDATE_WRITE);
		} else if (err < 0) {
			f2fs_write_failed(mapping, offset + count);
		}
	}

out:
	trace_f2fs_direct_IO_exit(inode, offset, count, rw, err);

	return err;
}