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
struct perf_evsel {int dummy; } ;
struct perf_evlist {int dummy; } ;
struct cpu_map {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 int TEST_FAIL ; 
 int TEST_OK ; 
 int TEST_SKIP ; 
 struct cpu_map* cpu_map__new (char*) ; 
 int /*<<< orphan*/  cpu_map__put (struct cpu_map*) ; 
 struct perf_evsel* perf_evlist__last (struct perf_evlist*) ; 
 int perf_evsel__open_per_cpu (struct perf_evsel*,struct cpu_map*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static int attach__cpu_enabled(struct perf_evlist *evlist)
{
	struct perf_evsel *evsel = perf_evlist__last(evlist);
	struct cpu_map *cpus;
	int err;

	pr_debug("attaching to CPU 0 as enabled\n");

	cpus = cpu_map__new("0");
	if (cpus == NULL) {
		pr_debug("failed to call cpu_map__new\n");
		return -1;
	}

	err = perf_evsel__open_per_cpu(evsel, cpus);
	if (err == -EACCES)
		return TEST_SKIP;

	cpu_map__put(cpus);
	return err ? TEST_FAIL : TEST_OK;
}