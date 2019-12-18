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
typedef  scalar_t__ u64 ;
struct file {struct eventfd_ctx* private_data; } ;
struct eventfd_ctx {int /*<<< orphan*/  count; int /*<<< orphan*/  wqh; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int /*<<< orphan*/  __poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLLERR ; 
 int /*<<< orphan*/  EPOLLIN ; 
 int /*<<< orphan*/  EPOLLOUT ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ ULLONG_MAX ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t eventfd_poll(struct file *file, poll_table *wait)
{
	struct eventfd_ctx *ctx = file->private_data;
	__poll_t events = 0;
	u64 count;

	poll_wait(file, &ctx->wqh, wait);

	/*
	 * All writes to ctx->count occur within ctx->wqh.lock.  This read
	 * can be done outside ctx->wqh.lock because we know that poll_wait
	 * takes that lock (through add_wait_queue) if our caller will sleep.
	 *
	 * The read _can_ therefore seep into add_wait_queue's critical
	 * section, but cannot move above it!  add_wait_queue's spin_lock acts
	 * as an acquire barrier and ensures that the read be ordered properly
	 * against the writes.  The following CAN happen and is safe:
	 *
	 *     poll                               write
	 *     -----------------                  ------------
	 *     lock ctx->wqh.lock (in poll_wait)
	 *     count = ctx->count
	 *     __add_wait_queue
	 *     unlock ctx->wqh.lock
	 *                                        lock ctx->qwh.lock
	 *                                        ctx->count += n
	 *                                        if (waitqueue_active)
	 *                                          wake_up_locked_poll
	 *                                        unlock ctx->qwh.lock
	 *     eventfd_poll returns 0
	 *
	 * but the following, which would miss a wakeup, cannot happen:
	 *
	 *     poll                               write
	 *     -----------------                  ------------
	 *     count = ctx->count (INVALID!)
	 *                                        lock ctx->qwh.lock
	 *                                        ctx->count += n
	 *                                        **waitqueue_active is false**
	 *                                        **no wake_up_locked_poll!**
	 *                                        unlock ctx->qwh.lock
	 *     lock ctx->wqh.lock (in poll_wait)
	 *     __add_wait_queue
	 *     unlock ctx->wqh.lock
	 *     eventfd_poll returns 0
	 */
	count = READ_ONCE(ctx->count);

	if (count > 0)
		events |= EPOLLIN;
	if (count == ULLONG_MAX)
		events |= EPOLLERR;
	if (ULLONG_MAX - 1 > count)
		events |= EPOLLOUT;

	return events;
}