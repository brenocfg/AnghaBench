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
struct io_ring_ctx {int flags; int /*<<< orphan*/  uring_lock; int /*<<< orphan*/  poll_list; } ;

/* Variables and functions */
 int IORING_SETUP_IOPOLL ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  io_iopoll_getevents (struct io_ring_ctx*,unsigned int*,int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void io_iopoll_reap_events(struct io_ring_ctx *ctx)
{
	if (!(ctx->flags & IORING_SETUP_IOPOLL))
		return;

	mutex_lock(&ctx->uring_lock);
	while (!list_empty(&ctx->poll_list)) {
		unsigned int nr_events = 0;

		io_iopoll_getevents(ctx, &nr_events, 1);

		/*
		 * Ensure we allow local-to-the-cpu processing to take place,
		 * in this case we need to ensure that we reap all events.
		 */
		cond_resched();
	}
	mutex_unlock(&ctx->uring_lock);
}