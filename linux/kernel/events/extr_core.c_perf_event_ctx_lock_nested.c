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
struct perf_event_context {int /*<<< orphan*/  mutex; int /*<<< orphan*/  refcount; } ;
struct perf_event {struct perf_event_context* ctx; } ;

/* Variables and functions */
 struct perf_event_context* READ_ONCE (struct perf_event_context*) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_ctx (struct perf_event_context*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  refcount_inc_not_zero (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct perf_event_context *
perf_event_ctx_lock_nested(struct perf_event *event, int nesting)
{
	struct perf_event_context *ctx;

again:
	rcu_read_lock();
	ctx = READ_ONCE(event->ctx);
	if (!refcount_inc_not_zero(&ctx->refcount)) {
		rcu_read_unlock();
		goto again;
	}
	rcu_read_unlock();

	mutex_lock_nested(&ctx->mutex, nesting);
	if (event->ctx != ctx) {
		mutex_unlock(&ctx->mutex);
		put_ctx(ctx);
		goto again;
	}

	return ctx;
}