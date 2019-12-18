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
struct TYPE_2__ {int /*<<< orphan*/ * threads; int /*<<< orphan*/ * cpus; } ;
struct evlist {TYPE_1__ core; } ;

/* Variables and functions */
 int /*<<< orphan*/  evlist__close (struct evlist*) ; 
 int /*<<< orphan*/  evlist__exit (struct evlist*) ; 
 int /*<<< orphan*/  evlist__munmap (struct evlist*) ; 
 int /*<<< orphan*/  evlist__purge (struct evlist*) ; 
 int /*<<< orphan*/  free (struct evlist*) ; 
 int /*<<< orphan*/  perf_cpu_map__put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_thread_map__put (int /*<<< orphan*/ *) ; 

void evlist__delete(struct evlist *evlist)
{
	if (evlist == NULL)
		return;

	evlist__munmap(evlist);
	evlist__close(evlist);
	perf_cpu_map__put(evlist->core.cpus);
	perf_thread_map__put(evlist->core.threads);
	evlist->core.cpus = NULL;
	evlist->core.threads = NULL;
	evlist__purge(evlist);
	evlist__exit(evlist);
	free(evlist);
}