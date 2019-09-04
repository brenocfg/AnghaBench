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
struct perf_event_context {int /*<<< orphan*/  mutex; } ;
struct perf_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_ctx (struct perf_event_context*) ; 

__attribute__((used)) static void perf_event_ctx_unlock(struct perf_event *event,
				  struct perf_event_context *ctx)
{
	mutex_unlock(&ctx->mutex);
	put_ctx(ctx);
}