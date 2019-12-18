#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sqe_submit {struct io_uring_sqe* sqe; } ;
struct kiocb {int ki_flags; unsigned int ki_ioprio; int /*<<< orphan*/  ki_complete; TYPE_2__* ki_filp; int /*<<< orphan*/  ki_hint; void* ki_pos; } ;
struct io_uring_sqe {int /*<<< orphan*/  rw_flags; int /*<<< orphan*/  ioprio; int /*<<< orphan*/  off; } ;
struct io_ring_ctx {int flags; } ;
struct io_kiocb {scalar_t__ result; int /*<<< orphan*/  flags; TYPE_3__* file; struct kiocb rw; struct io_ring_ctx* ctx; } ;
struct TYPE_10__ {int /*<<< orphan*/  i_mode; } ;
struct TYPE_9__ {int f_flags; } ;
struct TYPE_8__ {TYPE_1__* f_op; } ;
struct TYPE_7__ {int /*<<< orphan*/  iopoll; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBADF ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int IOCB_DIRECT ; 
 int IOCB_HIPRI ; 
 int IOCB_NOWAIT ; 
 int IORING_SETUP_IOPOLL ; 
 int O_NONBLOCK ; 
 void* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REQ_F_ISREG ; 
 int /*<<< orphan*/  REQ_F_MUST_PUNT ; 
 int /*<<< orphan*/  REQ_F_NOWAIT ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 TYPE_5__* file_inode (TYPE_3__*) ; 
 int /*<<< orphan*/  file_write_hint (TYPE_2__*) ; 
 unsigned int get_current_ioprio () ; 
 int /*<<< orphan*/  io_complete_rw ; 
 int /*<<< orphan*/  io_complete_rw_iopoll ; 
 int /*<<< orphan*/  io_file_supports_async (TYPE_3__*) ; 
 int iocb_flags (TYPE_2__*) ; 
 int ioprio_check_cap (unsigned int) ; 
 int /*<<< orphan*/  ki_hint_validate (int /*<<< orphan*/ ) ; 
 int kiocb_set_rw_flags (struct kiocb*,void*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int io_prep_rw(struct io_kiocb *req, const struct sqe_submit *s,
		      bool force_nonblock)
{
	const struct io_uring_sqe *sqe = s->sqe;
	struct io_ring_ctx *ctx = req->ctx;
	struct kiocb *kiocb = &req->rw;
	unsigned ioprio;
	int ret;

	if (!req->file)
		return -EBADF;

	if (S_ISREG(file_inode(req->file)->i_mode))
		req->flags |= REQ_F_ISREG;

	/*
	 * If the file doesn't support async, mark it as REQ_F_MUST_PUNT so
	 * we know to async punt it even if it was opened O_NONBLOCK
	 */
	if (force_nonblock && !io_file_supports_async(req->file)) {
		req->flags |= REQ_F_MUST_PUNT;
		return -EAGAIN;
	}

	kiocb->ki_pos = READ_ONCE(sqe->off);
	kiocb->ki_flags = iocb_flags(kiocb->ki_filp);
	kiocb->ki_hint = ki_hint_validate(file_write_hint(kiocb->ki_filp));

	ioprio = READ_ONCE(sqe->ioprio);
	if (ioprio) {
		ret = ioprio_check_cap(ioprio);
		if (ret)
			return ret;

		kiocb->ki_ioprio = ioprio;
	} else
		kiocb->ki_ioprio = get_current_ioprio();

	ret = kiocb_set_rw_flags(kiocb, READ_ONCE(sqe->rw_flags));
	if (unlikely(ret))
		return ret;

	/* don't allow async punt if RWF_NOWAIT was requested */
	if ((kiocb->ki_flags & IOCB_NOWAIT) ||
	    (req->file->f_flags & O_NONBLOCK))
		req->flags |= REQ_F_NOWAIT;

	if (force_nonblock)
		kiocb->ki_flags |= IOCB_NOWAIT;

	if (ctx->flags & IORING_SETUP_IOPOLL) {
		if (!(kiocb->ki_flags & IOCB_DIRECT) ||
		    !kiocb->ki_filp->f_op->iopoll)
			return -EOPNOTSUPP;

		kiocb->ki_flags |= IOCB_HIPRI;
		kiocb->ki_complete = io_complete_rw_iopoll;
		req->result = 0;
	} else {
		if (kiocb->ki_flags & IOCB_HIPRI)
			return -EINVAL;
		kiocb->ki_complete = io_complete_rw;
	}
	return 0;
}