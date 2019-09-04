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
struct perf_evlist {int /*<<< orphan*/ * threads; int /*<<< orphan*/ * cpus; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_map__put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct perf_evlist*) ; 
 int /*<<< orphan*/  perf_evlist__close (struct perf_evlist*) ; 
 int /*<<< orphan*/  perf_evlist__exit (struct perf_evlist*) ; 
 int /*<<< orphan*/  perf_evlist__munmap (struct perf_evlist*) ; 
 int /*<<< orphan*/  perf_evlist__purge (struct perf_evlist*) ; 
 int /*<<< orphan*/  thread_map__put (int /*<<< orphan*/ *) ; 

void perf_evlist__delete(struct perf_evlist *evlist)
{
	if (evlist == NULL)
		return;

	perf_evlist__munmap(evlist);
	perf_evlist__close(evlist);
	cpu_map__put(evlist->cpus);
	thread_map__put(evlist->threads);
	evlist->cpus = NULL;
	evlist->threads = NULL;
	perf_evlist__purge(evlist);
	perf_evlist__exit(evlist);
	free(evlist);
}