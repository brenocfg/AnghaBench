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

/* Variables and functions */
 int /*<<< orphan*/ * aggr_map ; 
 int /*<<< orphan*/  cpu_map__put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cpus_aggr_map ; 

__attribute__((used)) static void perf_stat__exit_aggr_mode(void)
{
	cpu_map__put(aggr_map);
	cpu_map__put(cpus_aggr_map);
	aggr_map = NULL;
	cpus_aggr_map = NULL;
}