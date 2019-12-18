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
struct target {int dummy; } ;
struct perf_stat_config {int /*<<< orphan*/ * stats; int /*<<< orphan*/ * output; } ;
struct perf_aggr_thread_value {int id; int /*<<< orphan*/  ena; int /*<<< orphan*/  run; int /*<<< orphan*/  uval; int /*<<< orphan*/  counter; } ;
struct TYPE_2__ {int /*<<< orphan*/  cpus; int /*<<< orphan*/  threads; } ;
struct evsel {TYPE_1__ core; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct perf_aggr_thread_value*) ; 
 int perf_cpu_map__nr (int /*<<< orphan*/ ) ; 
 int perf_thread_map__nr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printout (struct perf_stat_config*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt_stat ; 
 struct perf_aggr_thread_value* sort_aggr_thread (struct evsel*,int,int,int*,struct target*) ; 

__attribute__((used)) static void print_aggr_thread(struct perf_stat_config *config,
			      struct target *_target,
			      struct evsel *counter, char *prefix)
{
	FILE *output = config->output;
	int nthreads = perf_thread_map__nr(counter->core.threads);
	int ncpus = perf_cpu_map__nr(counter->core.cpus);
	int thread, sorted_threads, id;
	struct perf_aggr_thread_value *buf;

	buf = sort_aggr_thread(counter, nthreads, ncpus, &sorted_threads, _target);
	if (!buf) {
		perror("cannot sort aggr thread");
		return;
	}

	for (thread = 0; thread < sorted_threads; thread++) {
		if (prefix)
			fprintf(output, "%s", prefix);

		id = buf[thread].id;
		if (config->stats)
			printout(config, id, 0, buf[thread].counter, buf[thread].uval,
				 prefix, buf[thread].run, buf[thread].ena, 1.0,
				 &config->stats[id]);
		else
			printout(config, id, 0, buf[thread].counter, buf[thread].uval,
				 prefix, buf[thread].run, buf[thread].ena, 1.0,
				 &rt_stat);
		fputc('\n', output);
	}

	free(buf);
}