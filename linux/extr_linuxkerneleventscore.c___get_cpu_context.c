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
struct perf_event_context {TYPE_1__* pmu; } ;
struct perf_cpu_context {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pmu_cpu_context; } ;

/* Variables and functions */
 struct perf_cpu_context* this_cpu_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct perf_cpu_context *
__get_cpu_context(struct perf_event_context *ctx)
{
	return this_cpu_ptr(ctx->pmu->pmu_cpu_context);
}