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
typedef  scalar_t__ u16 ;
struct TYPE_6__ {int /*<<< orphan*/  entry; } ;
struct poll_iocb {int events; int /*<<< orphan*/  file; TYPE_1__* head; TYPE_3__ wait; scalar_t__ woken; int /*<<< orphan*/  work; } ;
struct kioctx {int /*<<< orphan*/  ctx_lock; int /*<<< orphan*/  active_reqs; } ;
struct iocb {scalar_t__ aio_buf; int /*<<< orphan*/  aio_fildes; scalar_t__ aio_rw_flags; scalar_t__ aio_nbytes; scalar_t__ aio_offset; } ;
struct TYPE_5__ {int _key; int /*<<< orphan*/  _qproc; } ;
struct aio_poll_table {int error; TYPE_2__ pt; struct aio_kiocb* iocb; } ;
struct aio_kiocb {int /*<<< orphan*/  ki_cancel; int /*<<< orphan*/  ki_list; int /*<<< orphan*/  ki_refcnt; struct poll_iocb poll; struct kioctx* ki_ctx; } ;
typedef  int ssize_t ;
typedef  int __poll_t ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EBADF ; 
 int EINVAL ; 
 int EPOLLERR ; 
 int EPOLLHUP ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aio_poll_cancel ; 
 int /*<<< orphan*/  aio_poll_complete (struct aio_kiocb*,int) ; 
 int /*<<< orphan*/  aio_poll_complete_work ; 
 int /*<<< orphan*/  aio_poll_queue_proc ; 
 int /*<<< orphan*/  aio_poll_wake ; 
 int demangle_poll (scalar_t__) ; 
 int /*<<< orphan*/  fget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_func_entry (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iocb_put (struct aio_kiocb*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int vfs_poll (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static ssize_t aio_poll(struct aio_kiocb *aiocb, struct iocb *iocb)
{
	struct kioctx *ctx = aiocb->ki_ctx;
	struct poll_iocb *req = &aiocb->poll;
	struct aio_poll_table apt;
	__poll_t mask;

	/* reject any unknown events outside the normal event mask. */
	if ((u16)iocb->aio_buf != iocb->aio_buf)
		return -EINVAL;
	/* reject fields that are not defined for poll */
	if (iocb->aio_offset || iocb->aio_nbytes || iocb->aio_rw_flags)
		return -EINVAL;

	INIT_WORK(&req->work, aio_poll_complete_work);
	req->events = demangle_poll(iocb->aio_buf) | EPOLLERR | EPOLLHUP;
	req->file = fget(iocb->aio_fildes);
	if (unlikely(!req->file))
		return -EBADF;

	apt.pt._qproc = aio_poll_queue_proc;
	apt.pt._key = req->events;
	apt.iocb = aiocb;
	apt.error = -EINVAL; /* same as no support for IOCB_CMD_POLL */

	/* initialized the list so that we can do list_empty checks */
	INIT_LIST_HEAD(&req->wait.entry);
	init_waitqueue_func_entry(&req->wait, aio_poll_wake);

	/* one for removal from waitqueue, one for this function */
	refcount_set(&aiocb->ki_refcnt, 2);

	mask = vfs_poll(req->file, &apt.pt) & req->events;
	if (unlikely(!req->head)) {
		/* we did not manage to set up a waitqueue, done */
		goto out;
	}

	spin_lock_irq(&ctx->ctx_lock);
	spin_lock(&req->head->lock);
	if (req->woken) {
		/* wake_up context handles the rest */
		mask = 0;
		apt.error = 0;
	} else if (mask || apt.error) {
		/* if we get an error or a mask we are done */
		WARN_ON_ONCE(list_empty(&req->wait.entry));
		list_del_init(&req->wait.entry);
	} else {
		/* actually waiting for an event */
		list_add_tail(&aiocb->ki_list, &ctx->active_reqs);
		aiocb->ki_cancel = aio_poll_cancel;
	}
	spin_unlock(&req->head->lock);
	spin_unlock_irq(&ctx->ctx_lock);

out:
	if (unlikely(apt.error)) {
		fput(req->file);
		return apt.error;
	}

	if (mask)
		aio_poll_complete(aiocb, mask);
	iocb_put(aiocb);
	return 0;
}