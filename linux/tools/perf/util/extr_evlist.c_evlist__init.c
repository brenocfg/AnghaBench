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
struct perf_thread_map {int dummy; } ;
struct perf_cpu_map {int dummy; } ;
struct TYPE_4__ {int pid; } ;
struct TYPE_5__ {int /*<<< orphan*/  pollfd; } ;
struct evlist {int /*<<< orphan*/  bkw_mmap_state; TYPE_1__ workload; TYPE_2__ core; } ;

/* Variables and functions */
 int /*<<< orphan*/  BKW_MMAP_NOTREADY ; 
 int /*<<< orphan*/  fdarray__init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  perf_evlist__init (TYPE_2__*) ; 
 int /*<<< orphan*/  perf_evlist__set_maps (TYPE_2__*,struct perf_cpu_map*,struct perf_thread_map*) ; 

void evlist__init(struct evlist *evlist, struct perf_cpu_map *cpus,
		  struct perf_thread_map *threads)
{
	perf_evlist__init(&evlist->core);
	perf_evlist__set_maps(&evlist->core, cpus, threads);
	fdarray__init(&evlist->core.pollfd, 64);
	evlist->workload.pid = -1;
	evlist->bkw_mmap_state = BKW_MMAP_NOTREADY;
}