#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sqe_submit {scalar_t__ index; scalar_t__ needs_lock; TYPE_1__* sqe; } ;
struct io_ring_ctx {scalar_t__ sq_entries; int flags; int /*<<< orphan*/  uring_lock; } ;
struct io_kiocb {int result; void* user_data; } ;
struct TYPE_8__ {int buf_index; int /*<<< orphan*/  opcode; int /*<<< orphan*/  user_data; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
#define  IORING_OP_FSYNC 139 
#define  IORING_OP_NOP 138 
#define  IORING_OP_POLL_ADD 137 
#define  IORING_OP_POLL_REMOVE 136 
#define  IORING_OP_READV 135 
#define  IORING_OP_READ_FIXED 134 
#define  IORING_OP_RECVMSG 133 
#define  IORING_OP_SENDMSG 132 
#define  IORING_OP_SYNC_FILE_RANGE 131 
#define  IORING_OP_TIMEOUT 130 
#define  IORING_OP_WRITEV 129 
#define  IORING_OP_WRITE_FIXED 128 
 int IORING_SETUP_IOPOLL ; 
 void* READ_ONCE (int /*<<< orphan*/ ) ; 
 int io_fsync (struct io_kiocb*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  io_iopoll_req_issued (struct io_kiocb*) ; 
 int io_nop (struct io_kiocb*,void*) ; 
 int io_poll_add (struct io_kiocb*,TYPE_1__*) ; 
 int io_poll_remove (struct io_kiocb*,TYPE_1__*) ; 
 int io_read (struct io_kiocb*,struct sqe_submit const*,int) ; 
 int io_recvmsg (struct io_kiocb*,TYPE_1__*,int) ; 
 int io_sendmsg (struct io_kiocb*,TYPE_1__*,int) ; 
 int io_sync_file_range (struct io_kiocb*,TYPE_1__*,int) ; 
 int io_timeout (struct io_kiocb*,TYPE_1__*) ; 
 int io_write (struct io_kiocb*,struct sqe_submit const*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int __io_submit_sqe(struct io_ring_ctx *ctx, struct io_kiocb *req,
			   const struct sqe_submit *s, bool force_nonblock)
{
	int ret, opcode;

	req->user_data = READ_ONCE(s->sqe->user_data);

	if (unlikely(s->index >= ctx->sq_entries))
		return -EINVAL;

	opcode = READ_ONCE(s->sqe->opcode);
	switch (opcode) {
	case IORING_OP_NOP:
		ret = io_nop(req, req->user_data);
		break;
	case IORING_OP_READV:
		if (unlikely(s->sqe->buf_index))
			return -EINVAL;
		ret = io_read(req, s, force_nonblock);
		break;
	case IORING_OP_WRITEV:
		if (unlikely(s->sqe->buf_index))
			return -EINVAL;
		ret = io_write(req, s, force_nonblock);
		break;
	case IORING_OP_READ_FIXED:
		ret = io_read(req, s, force_nonblock);
		break;
	case IORING_OP_WRITE_FIXED:
		ret = io_write(req, s, force_nonblock);
		break;
	case IORING_OP_FSYNC:
		ret = io_fsync(req, s->sqe, force_nonblock);
		break;
	case IORING_OP_POLL_ADD:
		ret = io_poll_add(req, s->sqe);
		break;
	case IORING_OP_POLL_REMOVE:
		ret = io_poll_remove(req, s->sqe);
		break;
	case IORING_OP_SYNC_FILE_RANGE:
		ret = io_sync_file_range(req, s->sqe, force_nonblock);
		break;
	case IORING_OP_SENDMSG:
		ret = io_sendmsg(req, s->sqe, force_nonblock);
		break;
	case IORING_OP_RECVMSG:
		ret = io_recvmsg(req, s->sqe, force_nonblock);
		break;
	case IORING_OP_TIMEOUT:
		ret = io_timeout(req, s->sqe);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	if (ret)
		return ret;

	if (ctx->flags & IORING_SETUP_IOPOLL) {
		if (req->result == -EAGAIN)
			return -EAGAIN;

		/* workqueue context doesn't hold uring_lock, grab it now */
		if (s->needs_lock)
			mutex_lock(&ctx->uring_lock);
		io_iopoll_req_issued(req);
		if (s->needs_lock)
			mutex_unlock(&ctx->uring_lock);
	}

	return 0;
}