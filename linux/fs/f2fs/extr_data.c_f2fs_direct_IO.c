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
struct inode {TYPE_2__* i_sb; } ;
struct f2fs_sb_info {int dummy; } ;
struct f2fs_inode_info {int /*<<< orphan*/ * i_gc_rwsem; } ;
struct address_space {struct inode* host; } ;
typedef  int ssize_t ;
typedef  scalar_t__ loff_t ;
typedef  enum rw_hint { ____Placeholder_rw_hint } rw_hint ;
struct TYPE_6__ {int whint_mode; } ;
struct TYPE_5__ {int /*<<< orphan*/  s_bdev; } ;
struct TYPE_4__ {struct address_space* f_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  APP_DIRECT_IO ; 
 int DIO_LOCKING ; 
 int DIO_SKIP_HOLES ; 
 int EAGAIN ; 
 struct f2fs_inode_info* F2FS_I (struct inode*) ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 TYPE_3__ F2FS_OPTION (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  FI_UPDATE_WRITE ; 
 int IOCB_NOWAIT ; 
 size_t READ ; 
 int WHINT_MODE_OFF ; 
 int WRITE ; 
 int WRITE_LIFE_NOT_SET ; 
 int __blockdev_direct_IO (struct kiocb*,struct inode*,int /*<<< orphan*/ ,struct iov_iter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int allow_outplace_dio (struct inode*,struct kiocb*,struct iov_iter*) ; 
 int check_direct_IO (struct inode*,struct iov_iter*,scalar_t__) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_read_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  f2fs_dio_submit_bio ; 
 scalar_t__ f2fs_force_buffered_io (struct inode*,struct kiocb*,struct iov_iter*) ; 
 int /*<<< orphan*/  f2fs_update_iostat (struct f2fs_sb_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  f2fs_write_failed (struct address_space*,scalar_t__) ; 
 int /*<<< orphan*/  get_data_block_dio ; 
 int /*<<< orphan*/  get_data_block_dio_write ; 
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
	struct f2fs_inode_info *fi = F2FS_I(inode);
	size_t count = iov_iter_count(iter);
	loff_t offset = iocb->ki_pos;
	int rw = iov_iter_rw(iter);
	int err;
	enum rw_hint hint = iocb->ki_hint;
	int whint_mode = F2FS_OPTION(sbi).whint_mode;
	bool do_opu;

	err = check_direct_IO(inode, iter, offset);
	if (err)
		return err < 0 ? err : 0;

	if (f2fs_force_buffered_io(inode, iocb, iter))
		return 0;

	do_opu = allow_outplace_dio(inode, iocb, iter);

	trace_f2fs_direct_IO_enter(inode, offset, count, rw);

	if (rw == WRITE && whint_mode == WHINT_MODE_OFF)
		iocb->ki_hint = WRITE_LIFE_NOT_SET;

	if (iocb->ki_flags & IOCB_NOWAIT) {
		if (!down_read_trylock(&fi->i_gc_rwsem[rw])) {
			iocb->ki_hint = hint;
			err = -EAGAIN;
			goto out;
		}
		if (do_opu && !down_read_trylock(&fi->i_gc_rwsem[READ])) {
			up_read(&fi->i_gc_rwsem[rw]);
			iocb->ki_hint = hint;
			err = -EAGAIN;
			goto out;
		}
	} else {
		down_read(&fi->i_gc_rwsem[rw]);
		if (do_opu)
			down_read(&fi->i_gc_rwsem[READ]);
	}

	err = __blockdev_direct_IO(iocb, inode, inode->i_sb->s_bdev,
			iter, rw == WRITE ? get_data_block_dio_write :
			get_data_block_dio, NULL, f2fs_dio_submit_bio,
			DIO_LOCKING | DIO_SKIP_HOLES);

	if (do_opu)
		up_read(&fi->i_gc_rwsem[READ]);

	up_read(&fi->i_gc_rwsem[rw]);

	if (rw == WRITE) {
		if (whint_mode == WHINT_MODE_OFF)
			iocb->ki_hint = hint;
		if (err > 0) {
			f2fs_update_iostat(F2FS_I_SB(inode), APP_DIRECT_IO,
									err);
			if (!do_opu)
				set_inode_flag(inode, FI_UPDATE_WRITE);
		} else if (err < 0) {
			f2fs_write_failed(mapping, offset + count);
		}
	}

out:
	trace_f2fs_direct_IO_exit(inode, offset, count, rw, err);

	return err;
}