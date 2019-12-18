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
struct io_wait_queue {scalar_t__ to_wait; scalar_t__ nr_timeouts; struct io_ring_ctx* ctx; } ;
struct io_ring_ctx {int /*<<< orphan*/  cq_timeouts; int /*<<< orphan*/  rings; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ io_cqring_events (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool io_should_wake(struct io_wait_queue *iowq)
{
	struct io_ring_ctx *ctx = iowq->ctx;

	/*
	 * Wake up if we have enough events, or if a timeout occured since we
	 * started waiting. For timeouts, we always want to return to userspace,
	 * regardless of event count.
	 */
	return io_cqring_events(ctx->rings) >= iowq->to_wait ||
			atomic_read(&ctx->cq_timeouts) != iowq->nr_timeouts;
}