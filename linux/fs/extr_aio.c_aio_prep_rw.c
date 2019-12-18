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
struct kiocb {int /*<<< orphan*/  ki_flags; int /*<<< orphan*/  ki_ioprio; int /*<<< orphan*/  ki_filp; int /*<<< orphan*/  ki_hint; int /*<<< orphan*/  ki_pos; int /*<<< orphan*/ * private; int /*<<< orphan*/  ki_complete; } ;
struct iocb {int aio_flags; int /*<<< orphan*/  aio_rw_flags; int /*<<< orphan*/  aio_reqprio; int /*<<< orphan*/  aio_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOCB_EVENTFD ; 
 int IOCB_FLAG_IOPRIO ; 
 int IOCB_FLAG_RESFD ; 
 int /*<<< orphan*/  IOCB_HIPRI ; 
 int /*<<< orphan*/  aio_complete_rw ; 
 int /*<<< orphan*/  file_write_hint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_current_ioprio () ; 
 int /*<<< orphan*/  iocb_flags (int /*<<< orphan*/ ) ; 
 int ioprio_check_cap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ki_hint_validate (int /*<<< orphan*/ ) ; 
 int kiocb_set_rw_flags (struct kiocb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int aio_prep_rw(struct kiocb *req, const struct iocb *iocb)
{
	int ret;

	req->ki_complete = aio_complete_rw;
	req->private = NULL;
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
			return ret;
		}

		req->ki_ioprio = iocb->aio_reqprio;
	} else
		req->ki_ioprio = get_current_ioprio();

	ret = kiocb_set_rw_flags(req, iocb->aio_rw_flags);
	if (unlikely(ret))
		return ret;

	req->ki_flags &= ~IOCB_HIPRI; /* no one is going to poll for this I/O */
	return 0;
}