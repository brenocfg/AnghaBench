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
struct io_ring_ctx {int /*<<< orphan*/  uring_lock; } ;

/* Variables and functions */
 int __io_iopoll_check (struct io_ring_ctx*,unsigned int*,long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int io_iopoll_check(struct io_ring_ctx *ctx, unsigned *nr_events,
			   long min)
{
	int ret;

	/*
	 * We disallow the app entering submit/complete with polling, but we
	 * still need to lock the ring to prevent racing with polled issue
	 * that got punted to a workqueue.
	 */
	mutex_lock(&ctx->uring_lock);
	ret = __io_iopoll_check(ctx, nr_events, min);
	mutex_unlock(&ctx->uring_lock);
	return ret;
}