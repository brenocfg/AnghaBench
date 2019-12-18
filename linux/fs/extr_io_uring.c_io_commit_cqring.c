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
struct io_ring_ctx {int dummy; } ;
struct io_kiocb {int flags; } ;

/* Variables and functions */
 int REQ_F_IO_DRAINED ; 
 int REQ_F_SHADOW_DRAIN ; 
 int /*<<< orphan*/  __io_commit_cqring (struct io_ring_ctx*) ; 
 int /*<<< orphan*/  __io_free_req (struct io_kiocb*) ; 
 struct io_kiocb* io_get_deferred_req (struct io_ring_ctx*) ; 
 struct io_kiocb* io_get_timeout_req (struct io_ring_ctx*) ; 
 int /*<<< orphan*/  io_kill_timeout (struct io_kiocb*) ; 
 int /*<<< orphan*/  io_queue_async_work (struct io_ring_ctx*,struct io_kiocb*) ; 

__attribute__((used)) static void io_commit_cqring(struct io_ring_ctx *ctx)
{
	struct io_kiocb *req;

	while ((req = io_get_timeout_req(ctx)) != NULL)
		io_kill_timeout(req);

	__io_commit_cqring(ctx);

	while ((req = io_get_deferred_req(ctx)) != NULL) {
		if (req->flags & REQ_F_SHADOW_DRAIN) {
			/* Just for drain, free it. */
			__io_free_req(req);
			continue;
		}
		req->flags |= REQ_F_IO_DRAINED;
		io_queue_async_work(ctx, req);
	}
}