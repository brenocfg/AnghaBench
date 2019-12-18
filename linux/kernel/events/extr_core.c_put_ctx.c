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
struct perf_event_context {scalar_t__ task; int /*<<< orphan*/  rcu_head; struct perf_event_context* parent_ctx; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 scalar_t__ TASK_TOMBSTONE ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_ctx ; 
 int /*<<< orphan*/  put_task_struct (scalar_t__) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void put_ctx(struct perf_event_context *ctx)
{
	if (refcount_dec_and_test(&ctx->refcount)) {
		if (ctx->parent_ctx)
			put_ctx(ctx->parent_ctx);
		if (ctx->task && ctx->task != TASK_TOMBSTONE)
			put_task_struct(ctx->task);
		call_rcu(&ctx->rcu_head, free_ctx);
	}
}