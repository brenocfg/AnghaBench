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
struct kiocb {int ki_flags; int /*<<< orphan*/  ki_pos; } ;
struct iovec {scalar_t__ iov_len; int /*<<< orphan*/  iov_base; } ;
struct iov_iter {int dummy; } ;
struct file {TYPE_1__* f_op; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_2__ {scalar_t__ (* read ) (struct file*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ;scalar_t__ (* write ) (struct file*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EOPNOTSUPP ; 
 int IOCB_HIPRI ; 
 int IOCB_NOWAIT ; 
 int READ ; 
 int /*<<< orphan*/  iov_iter_advance (struct iov_iter*,scalar_t__) ; 
 scalar_t__ iov_iter_count (struct iov_iter*) ; 
 struct iovec iov_iter_iovec (struct iov_iter*) ; 
 scalar_t__ stub1 (struct file*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (struct file*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t loop_rw_iter(int rw, struct file *file, struct kiocb *kiocb,
			   struct iov_iter *iter)
{
	ssize_t ret = 0;

	/*
	 * Don't support polled IO through this interface, and we can't
	 * support non-blocking either. For the latter, this just causes
	 * the kiocb to be handled from an async context.
	 */
	if (kiocb->ki_flags & IOCB_HIPRI)
		return -EOPNOTSUPP;
	if (kiocb->ki_flags & IOCB_NOWAIT)
		return -EAGAIN;

	while (iov_iter_count(iter)) {
		struct iovec iovec = iov_iter_iovec(iter);
		ssize_t nr;

		if (rw == READ) {
			nr = file->f_op->read(file, iovec.iov_base,
					      iovec.iov_len, &kiocb->ki_pos);
		} else {
			nr = file->f_op->write(file, iovec.iov_base,
					       iovec.iov_len, &kiocb->ki_pos);
		}

		if (nr < 0) {
			if (!ret)
				ret = nr;
			break;
		}
		ret += nr;
		if (nr != iovec.iov_len)
			break;
		iov_iter_advance(iter, nr);
	}

	return ret;
}