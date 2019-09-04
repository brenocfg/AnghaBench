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
struct perf_sample_id {int idx; int cpu; int tid; } ;
struct perf_evsel {int /*<<< orphan*/  system_wide; } ;
struct perf_evlist {scalar_t__ threads; TYPE_1__* cpus; } ;
struct TYPE_2__ {int* map; } ;

/* Variables and functions */
 struct perf_sample_id* SID (struct perf_evsel*,int,int) ; 
 int thread_map__pid (scalar_t__,int) ; 

__attribute__((used)) static void perf_evlist__set_sid_idx(struct perf_evlist *evlist,
				     struct perf_evsel *evsel, int idx, int cpu,
				     int thread)
{
	struct perf_sample_id *sid = SID(evsel, cpu, thread);
	sid->idx = idx;
	if (evlist->cpus && cpu >= 0)
		sid->cpu = evlist->cpus->map[cpu];
	else
		sid->cpu = -1;
	if (!evsel->system_wide && evlist->threads && thread >= 0)
		sid->tid = thread_map__pid(evlist->threads, thread);
	else
		sid->tid = -1;
}