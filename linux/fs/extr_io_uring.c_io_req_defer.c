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
struct io_uring_sqe {int dummy; } ;
struct io_ring_ctx {int /*<<< orphan*/  completion_lock; int /*<<< orphan*/  defer_list; } ;
struct TYPE_2__ {struct io_uring_sqe* sqe; } ;
struct io_kiocb {int /*<<< orphan*/  list; int /*<<< orphan*/  work; TYPE_1__ submit; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EIOCBQUEUED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_sequence_defer (struct io_ring_ctx*,struct io_kiocb*) ; 
 int /*<<< orphan*/  io_sq_wq_submit_work ; 
 int /*<<< orphan*/  kfree (struct io_uring_sqe*) ; 
 struct io_uring_sqe* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct io_uring_sqe*,struct io_uring_sqe const*,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int io_req_defer(struct io_ring_ctx *ctx, struct io_kiocb *req,
			const struct io_uring_sqe *sqe)
{
	struct io_uring_sqe *sqe_copy;

	if (!io_sequence_defer(ctx, req) && list_empty(&ctx->defer_list))
		return 0;

	sqe_copy = kmalloc(sizeof(*sqe_copy), GFP_KERNEL);
	if (!sqe_copy)
		return -EAGAIN;

	spin_lock_irq(&ctx->completion_lock);
	if (!io_sequence_defer(ctx, req) && list_empty(&ctx->defer_list)) {
		spin_unlock_irq(&ctx->completion_lock);
		kfree(sqe_copy);
		return 0;
	}

	memcpy(sqe_copy, sqe, sizeof(*sqe_copy));
	req->submit.sqe = sqe_copy;

	INIT_WORK(&req->work, io_sq_wq_submit_work);
	list_add_tail(&req->list, &ctx->defer_list);
	spin_unlock_irq(&ctx->completion_lock);
	return -EIOCBQUEUED;
}