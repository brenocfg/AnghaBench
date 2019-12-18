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
struct kiocb {int /*<<< orphan*/  ki_flags; int /*<<< orphan*/  ki_pos; struct file* ki_filp; } ;
struct iovec {int dummy; } ;
struct iov_iter {int dummy; } ;
struct iocb {int dummy; } ;
struct file {int f_mode; TYPE_1__* f_op; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; } ;
struct TYPE_3__ {int /*<<< orphan*/  write_iter; } ;

/* Variables and functions */
 int EBADF ; 
 int EINVAL ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  IOCB_WRITE ; 
 int /*<<< orphan*/  SB_FREEZE_WRITE ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int UIO_FASTIOV ; 
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  __sb_start_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __sb_writers_release (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int aio_prep_rw (struct kiocb*,struct iocb const*) ; 
 int /*<<< orphan*/  aio_rw_done (struct kiocb*,int /*<<< orphan*/ ) ; 
 int aio_setup_rw (int /*<<< orphan*/ ,struct iocb const*,struct iovec**,int,int,struct iov_iter*) ; 
 int /*<<< orphan*/  call_write_iter (struct file*,struct kiocb*,struct iov_iter*) ; 
 TYPE_2__* file_inode (struct file*) ; 
 int /*<<< orphan*/  iov_iter_count (struct iov_iter*) ; 
 int /*<<< orphan*/  kfree (struct iovec*) ; 
 int rw_verify_area (int /*<<< orphan*/ ,struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int aio_write(struct kiocb *req, const struct iocb *iocb,
			 bool vectored, bool compat)
{
	struct iovec inline_vecs[UIO_FASTIOV], *iovec = inline_vecs;
	struct iov_iter iter;
	struct file *file;
	int ret;

	ret = aio_prep_rw(req, iocb);
	if (ret)
		return ret;
	file = req->ki_filp;

	if (unlikely(!(file->f_mode & FMODE_WRITE)))
		return -EBADF;
	if (unlikely(!file->f_op->write_iter))
		return -EINVAL;

	ret = aio_setup_rw(WRITE, iocb, &iovec, vectored, compat, &iter);
	if (ret < 0)
		return ret;
	ret = rw_verify_area(WRITE, file, &req->ki_pos, iov_iter_count(&iter));
	if (!ret) {
		/*
		 * Open-code file_start_write here to grab freeze protection,
		 * which will be released by another thread in
		 * aio_complete_rw().  Fool lockdep by telling it the lock got
		 * released so that it doesn't complain about the held lock when
		 * we return to userspace.
		 */
		if (S_ISREG(file_inode(file)->i_mode)) {
			__sb_start_write(file_inode(file)->i_sb, SB_FREEZE_WRITE, true);
			__sb_writers_release(file_inode(file)->i_sb, SB_FREEZE_WRITE);
		}
		req->ki_flags |= IOCB_WRITE;
		aio_rw_done(req, call_write_iter(file, req, &iter));
	}
	kfree(iovec);
	return ret;
}