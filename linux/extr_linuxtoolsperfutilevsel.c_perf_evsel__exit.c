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
struct perf_evsel {int /*<<< orphan*/  name; int /*<<< orphan*/  group_name; int /*<<< orphan*/  threads; int /*<<< orphan*/  own_cpus; int /*<<< orphan*/  cpus; int /*<<< orphan*/  cgrp; int /*<<< orphan*/ * evlist; int /*<<< orphan*/  node; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* fini ) (struct perf_evsel*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgroup__put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_map__put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_evsel__free_config_terms (struct perf_evsel*) ; 
 int /*<<< orphan*/  perf_evsel__free_counts (struct perf_evsel*) ; 
 int /*<<< orphan*/  perf_evsel__free_fd (struct perf_evsel*) ; 
 int /*<<< orphan*/  perf_evsel__free_id (struct perf_evsel*) ; 
 TYPE_1__ perf_evsel__object ; 
 int /*<<< orphan*/  stub1 (struct perf_evsel*) ; 
 int /*<<< orphan*/  thread_map__put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

void perf_evsel__exit(struct perf_evsel *evsel)
{
	assert(list_empty(&evsel->node));
	assert(evsel->evlist == NULL);
	perf_evsel__free_counts(evsel);
	perf_evsel__free_fd(evsel);
	perf_evsel__free_id(evsel);
	perf_evsel__free_config_terms(evsel);
	cgroup__put(evsel->cgrp);
	cpu_map__put(evsel->cpus);
	cpu_map__put(evsel->own_cpus);
	thread_map__put(evsel->threads);
	zfree(&evsel->group_name);
	zfree(&evsel->name);
	perf_evsel__object.fini(evsel);
}