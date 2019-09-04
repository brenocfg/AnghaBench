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
struct thread_map {int /*<<< orphan*/  nr; } ;
struct perf_evsel {struct thread_map* threads; struct cpu_map* cpus; } ;
struct cpu_map {int /*<<< orphan*/  nr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int __store_counter_ids (struct perf_evsel*) ; 
 scalar_t__ perf_evsel__alloc_id (struct perf_evsel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int store_counter_ids(struct perf_evsel *counter)
{
	struct cpu_map *cpus = counter->cpus;
	struct thread_map *threads = counter->threads;

	if (perf_evsel__alloc_id(counter, cpus->nr, threads->nr))
		return -ENOMEM;

	return __store_counter_ids(counter);
}