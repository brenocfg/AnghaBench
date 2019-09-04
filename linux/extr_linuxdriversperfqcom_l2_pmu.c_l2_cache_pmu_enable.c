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
struct pmu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cluster_pmu_enable () ; 

__attribute__((used)) static void l2_cache_pmu_enable(struct pmu *pmu)
{
	/*
	 * Although there is only one PMU (per socket) controlling multiple
	 * physical PMUs (per cluster), because we do not support per-task mode
	 * each event is associated with a CPU. Each event has pmu_enable
	 * called on its CPU, so here it is only necessary to enable the
	 * counters for the current CPU.
	 */

	cluster_pmu_enable();
}