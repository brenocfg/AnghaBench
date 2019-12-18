#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct io_uring_sqe {int /*<<< orphan*/  poll_events; scalar_t__ buf_index; scalar_t__ len; scalar_t__ off; scalar_t__ ioprio; scalar_t__ addr; } ;
struct io_ring_ctx {int flags; int /*<<< orphan*/  completion_lock; int /*<<< orphan*/  cancel_list; } ;
struct TYPE_6__ {int _key; int /*<<< orphan*/  _qproc; } ;
struct io_poll_table {int error; TYPE_2__ pt; struct io_kiocb* req; } ;
struct TYPE_8__ {int /*<<< orphan*/  entry; } ;
struct io_poll_iocb {int events; int done; int canceled; TYPE_3__* head; TYPE_4__ wait; int /*<<< orphan*/  file; } ;
struct TYPE_5__ {int /*<<< orphan*/ * sqe; } ;
struct io_kiocb {int /*<<< orphan*/  list; int /*<<< orphan*/  work; TYPE_1__ submit; struct io_ring_ctx* ctx; struct io_poll_iocb poll; } ;
typedef  int __poll_t ;
struct TYPE_7__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EBADF ; 
 int EINVAL ; 
 int EPOLLERR ; 
 int EPOLLHUP ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IORING_SETUP_IOPOLL ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ONCE (int,int) ; 
 int demangle_poll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_func_entry (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_cqring_ev_posted (struct io_ring_ctx*) ; 
 int /*<<< orphan*/  io_poll_complete (struct io_ring_ctx*,struct io_kiocb*,int) ; 
 int /*<<< orphan*/  io_poll_complete_work ; 
 int /*<<< orphan*/  io_poll_queue_proc ; 
 int /*<<< orphan*/  io_poll_wake ; 
 int /*<<< orphan*/  io_put_req (struct io_kiocb*) ; 
 scalar_t__ likely (TYPE_3__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int vfs_poll (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int io_poll_add(struct io_kiocb *req, const struct io_uring_sqe *sqe)
{
	struct io_poll_iocb *poll = &req->poll;
	struct io_ring_ctx *ctx = req->ctx;
	struct io_poll_table ipt;
	bool cancel = false;
	__poll_t mask;
	u16 events;

	if (unlikely(req->ctx->flags & IORING_SETUP_IOPOLL))
		return -EINVAL;
	if (sqe->addr || sqe->ioprio || sqe->off || sqe->len || sqe->buf_index)
		return -EINVAL;
	if (!poll->file)
		return -EBADF;

	req->submit.sqe = NULL;
	INIT_WORK(&req->work, io_poll_complete_work);
	events = READ_ONCE(sqe->poll_events);
	poll->events = demangle_poll(events) | EPOLLERR | EPOLLHUP;

	poll->head = NULL;
	poll->done = false;
	poll->canceled = false;

	ipt.pt._qproc = io_poll_queue_proc;
	ipt.pt._key = poll->events;
	ipt.req = req;
	ipt.error = -EINVAL; /* same as no support for IOCB_CMD_POLL */

	/* initialized the list so that we can do list_empty checks */
	INIT_LIST_HEAD(&poll->wait.entry);
	init_waitqueue_func_entry(&poll->wait, io_poll_wake);

	INIT_LIST_HEAD(&req->list);

	mask = vfs_poll(poll->file, &ipt.pt) & poll->events;

	spin_lock_irq(&ctx->completion_lock);
	if (likely(poll->head)) {
		spin_lock(&poll->head->lock);
		if (unlikely(list_empty(&poll->wait.entry))) {
			if (ipt.error)
				cancel = true;
			ipt.error = 0;
			mask = 0;
		}
		if (mask || ipt.error)
			list_del_init(&poll->wait.entry);
		else if (cancel)
			WRITE_ONCE(poll->canceled, true);
		else if (!poll->done) /* actually waiting for an event */
			list_add_tail(&req->list, &ctx->cancel_list);
		spin_unlock(&poll->head->lock);
	}
	if (mask) { /* no async, we'd stolen it */
		ipt.error = 0;
		io_poll_complete(ctx, req, mask);
	}
	spin_unlock_irq(&ctx->completion_lock);

	if (mask) {
		io_cqring_ev_posted(ctx);
		io_put_req(req);
	}
	return ipt.error;
}