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
struct TYPE_2__ {int /*<<< orphan*/ * cpus_aggr_map; int /*<<< orphan*/ * aggr_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_cpu_map__put (int /*<<< orphan*/ *) ; 
 TYPE_1__ stat_config ; 

__attribute__((used)) static void perf_stat__exit_aggr_mode(void)
{
	perf_cpu_map__put(stat_config.aggr_map);
	perf_cpu_map__put(stat_config.cpus_aggr_map);
	stat_config.aggr_map = NULL;
	stat_config.cpus_aggr_map = NULL;
}