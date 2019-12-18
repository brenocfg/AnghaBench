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
struct io_ring_ctx {int /*<<< orphan*/ ** sqo_wq; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  io_sq_thread_stop (struct io_ring_ctx*) ; 

__attribute__((used)) static void io_finish_async(struct io_ring_ctx *ctx)
{
	int i;

	io_sq_thread_stop(ctx);

	for (i = 0; i < ARRAY_SIZE(ctx->sqo_wq); i++) {
		if (ctx->sqo_wq[i]) {
			destroy_workqueue(ctx->sqo_wq[i]);
			ctx->sqo_wq[i] = NULL;
		}
	}
}