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
struct sqe_submit {int /*<<< orphan*/  needs_lock; } ;
struct kiocb {int ki_flags; int /*<<< orphan*/  ki_pos; struct file* ki_filp; } ;
struct iovec {int dummy; } ;
struct iov_iter {int dummy; } ;
struct io_kiocb {int flags; int result; int /*<<< orphan*/  ctx; struct kiocb rw; } ;
struct file {int f_mode; TYPE_1__* f_op; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  i_sb; } ;
struct TYPE_3__ {scalar_t__ write_iter; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBADF ; 
 int FMODE_WRITE ; 
 int IOCB_DIRECT ; 
 int IOCB_WRITE ; 
 int REQ_F_ISREG ; 
 int REQ_F_LINK ; 
 int /*<<< orphan*/  SB_FREEZE_WRITE ; 
 int UIO_FASTIOV ; 
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  __sb_start_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __sb_writers_release (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int call_write_iter (struct file*,struct kiocb*,struct iov_iter*) ; 
 TYPE_2__* file_inode (struct file*) ; 
 int /*<<< orphan*/  io_async_list_note (int /*<<< orphan*/ ,struct io_kiocb*,size_t) ; 
 int io_import_iovec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sqe_submit const*,struct iovec**,struct iov_iter*) ; 
 int io_prep_rw (struct io_kiocb*,struct sqe_submit const*,int) ; 
 int /*<<< orphan*/  io_rw_done (struct kiocb*,int) ; 
 size_t iov_iter_count (struct iov_iter*) ; 
 int /*<<< orphan*/  kfree (struct iovec*) ; 
 int loop_rw_iter (int /*<<< orphan*/ ,struct file*,struct kiocb*,struct iov_iter*) ; 
 int rw_verify_area (int /*<<< orphan*/ ,struct file*,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int io_write(struct io_kiocb *req, const struct sqe_submit *s,
		    bool force_nonblock)
{
	struct iovec inline_vecs[UIO_FASTIOV], *iovec = inline_vecs;
	struct kiocb *kiocb = &req->rw;
	struct iov_iter iter;
	struct file *file;
	size_t iov_count;
	ssize_t ret;

	ret = io_prep_rw(req, s, force_nonblock);
	if (ret)
		return ret;

	file = kiocb->ki_filp;
	if (unlikely(!(file->f_mode & FMODE_WRITE)))
		return -EBADF;

	ret = io_import_iovec(req->ctx, WRITE, s, &iovec, &iter);
	if (ret < 0)
		return ret;

	if (req->flags & REQ_F_LINK)
		req->result = ret;

	iov_count = iov_iter_count(&iter);

	ret = -EAGAIN;
	if (force_nonblock && !(kiocb->ki_flags & IOCB_DIRECT)) {
		/* If ->needs_lock is true, we're already in async context. */
		if (!s->needs_lock)
			io_async_list_note(WRITE, req, iov_count);
		goto out_free;
	}

	ret = rw_verify_area(WRITE, file, &kiocb->ki_pos, iov_count);
	if (!ret) {
		ssize_t ret2;

		/*
		 * Open-code file_start_write here to grab freeze protection,
		 * which will be released by another thread in
		 * io_complete_rw().  Fool lockdep by telling it the lock got
		 * released so that it doesn't complain about the held lock when
		 * we return to userspace.
		 */
		if (req->flags & REQ_F_ISREG) {
			__sb_start_write(file_inode(file)->i_sb,
						SB_FREEZE_WRITE, true);
			__sb_writers_release(file_inode(file)->i_sb,
						SB_FREEZE_WRITE);
		}
		kiocb->ki_flags |= IOCB_WRITE;

		if (file->f_op->write_iter)
			ret2 = call_write_iter(file, kiocb, &iter);
		else
			ret2 = loop_rw_iter(WRITE, file, kiocb, &iter);
		if (!force_nonblock || ret2 != -EAGAIN) {
			io_rw_done(kiocb, ret2);
		} else {
			/*
			 * If ->needs_lock is true, we're already in async
			 * context.
			 */
			if (!s->needs_lock)
				io_async_list_note(WRITE, req, iov_count);
			ret = -EAGAIN;
		}
	}
out_free:
	kfree(iovec);
	return ret;
}