#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct perf_evsel {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  cpus; } ;
struct TYPE_5__ {int* map; } ;
struct TYPE_4__ {scalar_t__ aggr_mode; } ;

/* Variables and functions */
 scalar_t__ AGGR_GLOBAL ; 
 scalar_t__ AGGR_NONE ; 
 int aggr_get_id (int /*<<< orphan*/ ,int) ; 
 TYPE_3__* evsel_list ; 
 TYPE_2__* perf_evsel__cpus (struct perf_evsel*) ; 
 int perf_evsel__nr_cpus (struct perf_evsel*) ; 
 TYPE_1__ stat_config ; 

__attribute__((used)) static int first_shadow_cpu(struct perf_evsel *evsel, int id)
{
	int i;

	if (!aggr_get_id)
		return 0;

	if (stat_config.aggr_mode == AGGR_NONE)
		return id;

	if (stat_config.aggr_mode == AGGR_GLOBAL)
		return 0;

	for (i = 0; i < perf_evsel__nr_cpus(evsel); i++) {
		int cpu2 = perf_evsel__cpus(evsel)->map[i];

		if (aggr_get_id(evsel_list->cpus, cpu2) == id)
			return cpu2;
	}
	return 0;
}