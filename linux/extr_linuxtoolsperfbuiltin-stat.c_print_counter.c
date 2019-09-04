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
typedef  double u64 ;
struct perf_evsel {double scale; } ;
struct aggr_data {int cpu; double val; double ena; double run; } ;
struct TYPE_2__ {int /*<<< orphan*/ * output; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  collect_data (struct perf_evsel*,int /*<<< orphan*/ ,struct aggr_data*) ; 
 int /*<<< orphan*/  counter_cb ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int perf_evsel__nr_cpus (struct perf_evsel*) ; 
 int /*<<< orphan*/  printout (int,int /*<<< orphan*/ ,struct perf_evsel*,double,char*,double,double,double,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt_stat ; 
 TYPE_1__ stat_config ; 

__attribute__((used)) static void print_counter(struct perf_evsel *counter, char *prefix)
{
	FILE *output = stat_config.output;
	u64 ena, run, val;
	double uval;
	int cpu;

	for (cpu = 0; cpu < perf_evsel__nr_cpus(counter); cpu++) {
		struct aggr_data ad = { .cpu = cpu };

		if (!collect_data(counter, counter_cb, &ad))
			return;
		val = ad.val;
		ena = ad.ena;
		run = ad.run;

		if (prefix)
			fprintf(output, "%s", prefix);

		uval = val * counter->scale;
		printout(cpu, 0, counter, uval, prefix, run, ena, 1.0,
			 &rt_stat);

		fputc('\n', output);
	}
}