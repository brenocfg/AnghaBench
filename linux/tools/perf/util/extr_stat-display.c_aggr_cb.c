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
struct perf_stat_config {int (* aggr_get_id ) (struct perf_stat_config*,int /*<<< orphan*/ ,int) ;} ;
struct perf_counts_values {scalar_t__ ena; scalar_t__ run; scalar_t__ val; } ;
struct evsel {TYPE_1__* counts; } ;
struct aggr_data {int id; scalar_t__ ena; scalar_t__ run; int /*<<< orphan*/  val; int /*<<< orphan*/  nr; } ;
struct TYPE_2__ {int scaled; } ;

/* Variables and functions */
 int /*<<< orphan*/  evsel__cpus (struct evsel*) ; 
 struct perf_counts_values* perf_counts (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int perf_evsel__nr_cpus (struct evsel*) ; 
 int stub1 (struct perf_stat_config*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void aggr_cb(struct perf_stat_config *config,
		    struct evsel *counter, void *data, bool first)
{
	struct aggr_data *ad = data;
	int cpu, s2;

	for (cpu = 0; cpu < perf_evsel__nr_cpus(counter); cpu++) {
		struct perf_counts_values *counts;

		s2 = config->aggr_get_id(config, evsel__cpus(counter), cpu);
		if (s2 != ad->id)
			continue;
		if (first)
			ad->nr++;
		counts = perf_counts(counter->counts, cpu, 0);
		/*
		 * When any result is bad, make them all to give
		 * consistent output in interval mode.
		 */
		if (counts->ena == 0 || counts->run == 0 ||
		    counter->counts->scaled == -1) {
			ad->ena = 0;
			ad->run = 0;
			break;
		}
		ad->val += counts->val;
		ad->ena += counts->ena;
		ad->run += counts->run;
	}
}