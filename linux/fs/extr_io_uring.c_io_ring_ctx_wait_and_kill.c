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
struct io_ring_ctx {int /*<<< orphan*/  ctx_done; int /*<<< orphan*/  uring_lock; int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  io_iopoll_reap_events (struct io_ring_ctx*) ; 
 int /*<<< orphan*/  io_kill_timeouts (struct io_ring_ctx*) ; 
 int /*<<< orphan*/  io_poll_remove_all (struct io_ring_ctx*) ; 
 int /*<<< orphan*/  io_ring_ctx_free (struct io_ring_ctx*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_ref_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void io_ring_ctx_wait_and_kill(struct io_ring_ctx *ctx)
{
	mutex_lock(&ctx->uring_lock);
	percpu_ref_kill(&ctx->refs);
	mutex_unlock(&ctx->uring_lock);

	io_kill_timeouts(ctx);
	io_poll_remove_all(ctx);
	io_iopoll_reap_events(ctx);
	wait_for_completion(&ctx->ctx_done);
	io_ring_ctx_free(ctx);
}