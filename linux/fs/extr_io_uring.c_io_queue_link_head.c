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
struct sqe_submit {TYPE_1__* sqe; } ;
struct io_ring_ctx {int /*<<< orphan*/  completion_lock; int /*<<< orphan*/  defer_list; } ;
struct io_kiocb {int /*<<< orphan*/  list; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  user_data; } ;

/* Variables and functions */
 int EIOCBQUEUED ; 
 int /*<<< orphan*/  REQ_F_IO_DRAIN ; 
 int /*<<< orphan*/  __io_free_req (struct io_kiocb*) ; 
 int __io_queue_sqe (struct io_ring_ctx*,struct io_kiocb*,struct sqe_submit*) ; 
 int /*<<< orphan*/  io_cqring_add_event (struct io_ring_ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  io_free_req (struct io_kiocb*) ; 
 int io_queue_sqe (struct io_ring_ctx*,struct io_kiocb*,struct sqe_submit*) ; 
 int io_req_defer (struct io_ring_ctx*,struct io_kiocb*,TYPE_1__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int io_queue_link_head(struct io_ring_ctx *ctx, struct io_kiocb *req,
			      struct sqe_submit *s, struct io_kiocb *shadow)
{
	int ret;
	int need_submit = false;

	if (!shadow)
		return io_queue_sqe(ctx, req, s);

	/*
	 * Mark the first IO in link list as DRAIN, let all the following
	 * IOs enter the defer list. all IO needs to be completed before link
	 * list.
	 */
	req->flags |= REQ_F_IO_DRAIN;
	ret = io_req_defer(ctx, req, s->sqe);
	if (ret) {
		if (ret != -EIOCBQUEUED) {
			io_free_req(req);
			__io_free_req(shadow);
			io_cqring_add_event(ctx, s->sqe->user_data, ret);
			return 0;
		}
	} else {
		/*
		 * If ret == 0 means that all IOs in front of link io are
		 * running done. let's queue link head.
		 */
		need_submit = true;
	}

	/* Insert shadow req to defer_list, blocking next IOs */
	spin_lock_irq(&ctx->completion_lock);
	list_add_tail(&shadow->list, &ctx->defer_list);
	spin_unlock_irq(&ctx->completion_lock);

	if (need_submit)
		return __io_queue_sqe(ctx, req, s);

	return 0;
}