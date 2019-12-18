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
struct io_uring_params {int /*<<< orphan*/  flags; } ;
struct io_ring_ctx {int /*<<< orphan*/  timeout_list; int /*<<< orphan*/  defer_list; int /*<<< orphan*/  cancel_list; int /*<<< orphan*/  poll_list; int /*<<< orphan*/  completion_lock; TYPE_1__* pending_async; int /*<<< orphan*/  wait; int /*<<< orphan*/  uring_lock; int /*<<< orphan*/  sqo_thread_started; int /*<<< orphan*/  ctx_done; int /*<<< orphan*/  cq_wait; int /*<<< orphan*/  flags; int /*<<< orphan*/  refs; } ;
struct TYPE_2__ {int /*<<< orphan*/  cnt; int /*<<< orphan*/  list; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PERCPU_REF_ALLOW_REINIT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  io_ring_ctx_ref_free ; 
 int /*<<< orphan*/  kfree (struct io_ring_ctx*) ; 
 struct io_ring_ctx* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ percpu_ref_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct io_ring_ctx *io_ring_ctx_alloc(struct io_uring_params *p)
{
	struct io_ring_ctx *ctx;
	int i;

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return NULL;

	if (percpu_ref_init(&ctx->refs, io_ring_ctx_ref_free,
			    PERCPU_REF_ALLOW_REINIT, GFP_KERNEL)) {
		kfree(ctx);
		return NULL;
	}

	ctx->flags = p->flags;
	init_waitqueue_head(&ctx->cq_wait);
	init_completion(&ctx->ctx_done);
	init_completion(&ctx->sqo_thread_started);
	mutex_init(&ctx->uring_lock);
	init_waitqueue_head(&ctx->wait);
	for (i = 0; i < ARRAY_SIZE(ctx->pending_async); i++) {
		spin_lock_init(&ctx->pending_async[i].lock);
		INIT_LIST_HEAD(&ctx->pending_async[i].list);
		atomic_set(&ctx->pending_async[i].cnt, 0);
	}
	spin_lock_init(&ctx->completion_lock);
	INIT_LIST_HEAD(&ctx->poll_list);
	INIT_LIST_HEAD(&ctx->cancel_list);
	INIT_LIST_HEAD(&ctx->defer_list);
	INIT_LIST_HEAD(&ctx->timeout_list);
	return ctx;
}