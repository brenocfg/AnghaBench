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
struct perf_event_context {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct perf_cpu_context {TYPE_1__ ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void perf_ctx_unlock(struct perf_cpu_context *cpuctx,
			    struct perf_event_context *ctx)
{
	if (ctx)
		raw_spin_unlock(&ctx->lock);
	raw_spin_unlock(&cpuctx->ctx.lock);
}