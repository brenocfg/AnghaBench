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
struct perf_evsel {int /*<<< orphan*/  cpus; int /*<<< orphan*/  threads; } ;
struct perf_aggr_thread_value {int id; int /*<<< orphan*/  ena; int /*<<< orphan*/  run; int /*<<< orphan*/  uval; int /*<<< orphan*/  counter; } ;
struct TYPE_2__ {int /*<<< orphan*/ * stats; int /*<<< orphan*/ * output; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int cpu_map__nr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct perf_aggr_thread_value*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printout (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt_stat ; 
 struct perf_aggr_thread_value* sort_aggr_thread (struct perf_evsel*,int,int,int*) ; 
 TYPE_1__ stat_config ; 
 int thread_map__nr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_aggr_thread(struct perf_evsel *counter, char *prefix)
{
	FILE *output = stat_config.output;
	int nthreads = thread_map__nr(counter->threads);
	int ncpus = cpu_map__nr(counter->cpus);
	int thread, sorted_threads, id;
	struct perf_aggr_thread_value *buf;

	buf = sort_aggr_thread(counter, nthreads, ncpus, &sorted_threads);
	if (!buf) {
		perror("cannot sort aggr thread");
		return;
	}

	for (thread = 0; thread < sorted_threads; thread++) {
		if (prefix)
			fprintf(output, "%s", prefix);

		id = buf[thread].id;
		if (stat_config.stats)
			printout(id, 0, buf[thread].counter, buf[thread].uval,
				 prefix, buf[thread].run, buf[thread].ena, 1.0,
				 &stat_config.stats[id]);
		else
			printout(id, 0, buf[thread].counter, buf[thread].uval,
				 prefix, buf[thread].run, buf[thread].ena, 1.0,
				 &rt_stat);
		fputc('\n', output);
	}

	free(buf);
}