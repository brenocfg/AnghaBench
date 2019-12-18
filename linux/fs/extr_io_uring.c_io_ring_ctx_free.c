#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct io_ring_ctx {int /*<<< orphan*/  user; int /*<<< orphan*/  cq_entries; int /*<<< orphan*/  sq_entries; scalar_t__ account_mem; int /*<<< orphan*/  refs; int /*<<< orphan*/  sq_sqes; int /*<<< orphan*/  rings; TYPE_1__* ring_sock; scalar_t__ sqo_mm; } ;
struct TYPE_2__ {int /*<<< orphan*/ * file; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_uid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_eventfd_unregister (struct io_ring_ctx*) ; 
 int /*<<< orphan*/  io_finish_async (struct io_ring_ctx*) ; 
 int /*<<< orphan*/  io_iopoll_reap_events (struct io_ring_ctx*) ; 
 int /*<<< orphan*/  io_mem_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_sqe_buffer_unregister (struct io_ring_ctx*) ; 
 int /*<<< orphan*/  io_sqe_files_unregister (struct io_ring_ctx*) ; 
 int /*<<< orphan*/  io_unaccount_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct io_ring_ctx*) ; 
 int /*<<< orphan*/  mmdrop (scalar_t__) ; 
 int /*<<< orphan*/  percpu_ref_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ring_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_release (TYPE_1__*) ; 

__attribute__((used)) static void io_ring_ctx_free(struct io_ring_ctx *ctx)
{
	io_finish_async(ctx);
	if (ctx->sqo_mm)
		mmdrop(ctx->sqo_mm);

	io_iopoll_reap_events(ctx);
	io_sqe_buffer_unregister(ctx);
	io_sqe_files_unregister(ctx);
	io_eventfd_unregister(ctx);

#if defined(CONFIG_UNIX)
	if (ctx->ring_sock) {
		ctx->ring_sock->file = NULL; /* so that iput() is called */
		sock_release(ctx->ring_sock);
	}
#endif

	io_mem_free(ctx->rings);
	io_mem_free(ctx->sq_sqes);

	percpu_ref_exit(&ctx->refs);
	if (ctx->account_mem)
		io_unaccount_mem(ctx->user,
				ring_pages(ctx->sq_entries, ctx->cq_entries));
	free_uid(ctx->user);
	kfree(ctx);
}