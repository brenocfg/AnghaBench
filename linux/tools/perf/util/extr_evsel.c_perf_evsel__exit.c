#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  threads; int /*<<< orphan*/  own_cpus; int /*<<< orphan*/  cpus; int /*<<< orphan*/  node; } ;
struct evsel {int /*<<< orphan*/  name; int /*<<< orphan*/  group_name; TYPE_2__ core; int /*<<< orphan*/  cgrp; int /*<<< orphan*/ * evlist; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* fini ) (struct evsel*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgroup__put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_cpu_map__put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_evsel__free_config_terms (struct evsel*) ; 
 int /*<<< orphan*/  perf_evsel__free_counts (struct evsel*) ; 
 int /*<<< orphan*/  perf_evsel__free_fd (TYPE_2__*) ; 
 int /*<<< orphan*/  perf_evsel__free_id (TYPE_2__*) ; 
 TYPE_1__ perf_evsel__object ; 
 int /*<<< orphan*/  perf_thread_map__put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct evsel*) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

void perf_evsel__exit(struct evsel *evsel)
{
	assert(list_empty(&evsel->core.node));
	assert(evsel->evlist == NULL);
	perf_evsel__free_counts(evsel);
	perf_evsel__free_fd(&evsel->core);
	perf_evsel__free_id(&evsel->core);
	perf_evsel__free_config_terms(evsel);
	cgroup__put(evsel->cgrp);
	perf_cpu_map__put(evsel->core.cpus);
	perf_cpu_map__put(evsel->core.own_cpus);
	perf_thread_map__put(evsel->core.threads);
	zfree(&evsel->group_name);
	zfree(&evsel->name);
	perf_evsel__object.fini(evsel);
}