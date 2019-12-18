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
struct perf_event_context {int /*<<< orphan*/  refcount; int /*<<< orphan*/  flexible_active; int /*<<< orphan*/  pinned_active; int /*<<< orphan*/  event_list; int /*<<< orphan*/  flexible_groups; int /*<<< orphan*/  pinned_groups; int /*<<< orphan*/  active_ctx_list; int /*<<< orphan*/  mutex; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_event_groups_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void __perf_event_init_context(struct perf_event_context *ctx)
{
	raw_spin_lock_init(&ctx->lock);
	mutex_init(&ctx->mutex);
	INIT_LIST_HEAD(&ctx->active_ctx_list);
	perf_event_groups_init(&ctx->pinned_groups);
	perf_event_groups_init(&ctx->flexible_groups);
	INIT_LIST_HEAD(&ctx->event_list);
	INIT_LIST_HEAD(&ctx->pinned_active);
	INIT_LIST_HEAD(&ctx->flexible_active);
	refcount_set(&ctx->refcount, 1);
}