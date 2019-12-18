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
struct kiocb {int /*<<< orphan*/  ki_pos; struct file* ki_filp; } ;
struct iovec {int dummy; } ;
struct iov_iter {int dummy; } ;
struct iocb {int dummy; } ;
struct file {int f_mode; TYPE_1__* f_op; } ;
struct TYPE_2__ {int /*<<< orphan*/  read_iter; } ;

/* Variables and functions */
 int EBADF ; 
 int EINVAL ; 
 int FMODE_READ ; 
 int /*<<< orphan*/  READ ; 
 int UIO_FASTIOV ; 
 int aio_prep_rw (struct kiocb*,struct iocb const*) ; 
 int /*<<< orphan*/  aio_rw_done (struct kiocb*,int /*<<< orphan*/ ) ; 
 int aio_setup_rw (int /*<<< orphan*/ ,struct iocb const*,struct iovec**,int,int,struct iov_iter*) ; 
 int /*<<< orphan*/  call_read_iter (struct file*,struct kiocb*,struct iov_iter*) ; 
 int /*<<< orphan*/  iov_iter_count (struct iov_iter*) ; 
 int /*<<< orphan*/  kfree (struct iovec*) ; 
 int rw_verify_area (int /*<<< orphan*/ ,struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int aio_read(struct kiocb *req, const struct iocb *iocb,
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
	if (unlikely(!(file->f_mode & FMODE_READ)))
		return -EBADF;
	ret = -EINVAL;
	if (unlikely(!file->f_op->read_iter))
		return -EINVAL;

	ret = aio_setup_rw(READ, iocb, &iovec, vectored, compat, &iter);
	if (ret < 0)
		return ret;
	ret = rw_verify_area(READ, file, &req->ki_pos, iov_iter_count(&iter));
	if (!ret)
		aio_rw_done(req, call_read_iter(file, req, &iter));
	kfree(iovec);
	return ret;
}