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
struct kiocb {int /*<<< orphan*/  ki_filp; int /*<<< orphan*/  ki_ioprio; int /*<<< orphan*/  ki_hint; int /*<<< orphan*/  ki_flags; int /*<<< orphan*/  ki_pos; int /*<<< orphan*/  ki_complete; } ;
struct iocb {int aio_flags; int /*<<< orphan*/  aio_rw_flags; int /*<<< orphan*/  aio_reqprio; int /*<<< orphan*/  aio_offset; int /*<<< orphan*/  aio_fildes; } ;

/* Variables and functions */
 int EBADF ; 
 int /*<<< orphan*/  IOCB_EVENTFD ; 
 int IOCB_FLAG_IOPRIO ; 
 int IOCB_FLAG_RESFD ; 
 int /*<<< orphan*/  IOPRIO_CLASS_NONE ; 
 int /*<<< orphan*/  IOPRIO_PRIO_VALUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aio_complete_rw ; 
 int /*<<< orphan*/  fget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_write_hint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iocb_flags (int /*<<< orphan*/ ) ; 
 int ioprio_check_cap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ki_hint_validate (int /*<<< orphan*/ ) ; 
 int kiocb_set_rw_flags (struct kiocb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int aio_prep_rw(struct kiocb *req, struct iocb *iocb)
{
	int ret;

	req->ki_filp = fget(iocb->aio_fildes);
	if (unlikely(!req->ki_filp))
		return -EBADF;
	req->ki_complete = aio_complete_rw;
	req->ki_pos = iocb->aio_offset;
	req->ki_flags = iocb_flags(req->ki_filp);
	if (iocb->aio_flags & IOCB_FLAG_RESFD)
		req->ki_flags |= IOCB_EVENTFD;
	req->ki_hint = ki_hint_validate(file_write_hint(req->ki_filp));
	if (iocb->aio_flags & IOCB_FLAG_IOPRIO) {
		/*
		 * If the IOCB_FLAG_IOPRIO flag of aio_flags is set, then
		 * aio_reqprio is interpreted as an I/O scheduling
		 * class and priority.
		 */
		ret = ioprio_check_cap(iocb->aio_reqprio);
		if (ret) {
			pr_debug("aio ioprio check cap error: %d\n", ret);
			fput(req->ki_filp);
			return ret;
		}

		req->ki_ioprio = iocb->aio_reqprio;
	} else
		req->ki_ioprio = IOPRIO_PRIO_VALUE(IOPRIO_CLASS_NONE, 0);

	ret = kiocb_set_rw_flags(req, iocb->aio_rw_flags);
	if (unlikely(ret))
		fput(req->ki_filp);
	return ret;
}