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
typedef  double u64 ;
struct perf_stat_config {int /*<<< orphan*/ * output; } ;
struct evsel {double scale; } ;
struct aggr_data {int cpu; double val; double ena; double run; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  collect_data (struct perf_stat_config*,struct evsel*,int /*<<< orphan*/ ,struct aggr_data*) ; 
 int /*<<< orphan*/  counter_cb ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int perf_evsel__nr_cpus (struct evsel*) ; 
 int /*<<< orphan*/  printout (struct perf_stat_config*,int,int /*<<< orphan*/ ,struct evsel*,double,char*,double,double,double,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt_stat ; 

__attribute__((used)) static void print_counter(struct perf_stat_config *config,
			  struct evsel *counter, char *prefix)
{
	FILE *output = config->output;
	u64 ena, run, val;
	double uval;
	int cpu;

	for (cpu = 0; cpu < perf_evsel__nr_cpus(counter); cpu++) {
		struct aggr_data ad = { .cpu = cpu };

		if (!collect_data(config, counter, counter_cb, &ad))
			return;
		val = ad.val;
		ena = ad.ena;
		run = ad.run;

		if (prefix)
			fprintf(output, "%s", prefix);

		uval = val * counter->scale;
		printout(config, cpu, 0, counter, uval, prefix, run, ena, 1.0,
			 &rt_stat);

		fputc('\n', output);
	}
}