#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct perf_stat_config {int (* aggr_get_id ) (struct perf_stat_config*,int /*<<< orphan*/ ,int) ;scalar_t__ aggr_mode; } ;
struct evsel {struct evlist* evlist; } ;
struct TYPE_3__ {int /*<<< orphan*/  cpus; } ;
struct evlist {TYPE_1__ core; } ;
struct TYPE_4__ {int* map; } ;

/* Variables and functions */
 scalar_t__ AGGR_GLOBAL ; 
 scalar_t__ AGGR_NONE ; 
 TYPE_2__* evsel__cpus (struct evsel*) ; 
 int perf_evsel__nr_cpus (struct evsel*) ; 
 int stub1 (struct perf_stat_config*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int first_shadow_cpu(struct perf_stat_config *config,
			    struct evsel *evsel, int id)
{
	struct evlist *evlist = evsel->evlist;
	int i;

	if (!config->aggr_get_id)
		return 0;

	if (config->aggr_mode == AGGR_NONE)
		return id;

	if (config->aggr_mode == AGGR_GLOBAL)
		return 0;

	for (i = 0; i < perf_evsel__nr_cpus(evsel); i++) {
		int cpu2 = evsel__cpus(evsel)->map[i];

		if (config->aggr_get_id(config, evlist->core.cpus, cpu2) == id)
			return cpu2;
	}
	return 0;
}