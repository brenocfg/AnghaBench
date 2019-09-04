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
struct sched_in_data {int can_add_hw; struct perf_cpu_context* cpuctx; struct perf_event_context* ctx; } ;
struct perf_event_context {int /*<<< orphan*/  flexible_groups; } ;
struct perf_cpu_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  flexible_sched_in ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  visit_groups_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sched_in_data*) ; 

__attribute__((used)) static void
ctx_flexible_sched_in(struct perf_event_context *ctx,
		      struct perf_cpu_context *cpuctx)
{
	struct sched_in_data sid = {
		.ctx = ctx,
		.cpuctx = cpuctx,
		.can_add_hw = 1,
	};

	visit_groups_merge(&ctx->flexible_groups,
			   smp_processor_id(),
			   flexible_sched_in, &sid);
}