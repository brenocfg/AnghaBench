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
struct pmu {int /*<<< orphan*/  pmu_cpu_context; } ;
struct perf_cpu_context {int /*<<< orphan*/  sched_cb_entry; int /*<<< orphan*/  sched_cb_usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_sched_cb_usages ; 
 int /*<<< orphan*/  this_cpu_dec (int /*<<< orphan*/ ) ; 
 struct perf_cpu_context* this_cpu_ptr (int /*<<< orphan*/ ) ; 

void perf_sched_cb_dec(struct pmu *pmu)
{
	struct perf_cpu_context *cpuctx = this_cpu_ptr(pmu->pmu_cpu_context);

	this_cpu_dec(perf_sched_cb_usages);

	if (!--cpuctx->sched_cb_usage)
		list_del(&cpuctx->sched_cb_entry);
}