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
struct TYPE_3__ {int /*<<< orphan*/  error; } ;
struct TYPE_4__ {TYPE_1__ h; } ;
struct fuse_req {int /*<<< orphan*/  flags; int /*<<< orphan*/  waitq; TYPE_2__ out; int /*<<< orphan*/  list; } ;
struct fuse_iqueue {int /*<<< orphan*/  lock; } ;
struct fuse_conn {int /*<<< orphan*/  no_interrupt; struct fuse_iqueue iq; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINTR ; 
 int /*<<< orphan*/  FR_FINISHED ; 
 int /*<<< orphan*/  FR_FORCE ; 
 int /*<<< orphan*/  FR_INTERRUPTED ; 
 int /*<<< orphan*/  FR_PENDING ; 
 int /*<<< orphan*/  FR_SENT ; 
 int /*<<< orphan*/  __fuse_put_request (struct fuse_req*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_interrupt (struct fuse_iqueue*,struct fuse_req*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,scalar_t__) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,scalar_t__) ; 
 int wait_event_killable (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void request_wait_answer(struct fuse_conn *fc, struct fuse_req *req)
{
	struct fuse_iqueue *fiq = &fc->iq;
	int err;

	if (!fc->no_interrupt) {
		/* Any signal may interrupt this */
		err = wait_event_interruptible(req->waitq,
					test_bit(FR_FINISHED, &req->flags));
		if (!err)
			return;

		set_bit(FR_INTERRUPTED, &req->flags);
		/* matches barrier in fuse_dev_do_read() */
		smp_mb__after_atomic();
		if (test_bit(FR_SENT, &req->flags))
			queue_interrupt(fiq, req);
	}

	if (!test_bit(FR_FORCE, &req->flags)) {
		/* Only fatal signals may interrupt this */
		err = wait_event_killable(req->waitq,
					test_bit(FR_FINISHED, &req->flags));
		if (!err)
			return;

		spin_lock(&fiq->lock);
		/* Request is not yet in userspace, bail out */
		if (test_bit(FR_PENDING, &req->flags)) {
			list_del(&req->list);
			spin_unlock(&fiq->lock);
			__fuse_put_request(req);
			req->out.h.error = -EINTR;
			return;
		}
		spin_unlock(&fiq->lock);
	}

	/*
	 * Either request is already in userspace, or it was forced.
	 * Wait it out.
	 */
	wait_event(req->waitq, test_bit(FR_FINISHED, &req->flags));
}