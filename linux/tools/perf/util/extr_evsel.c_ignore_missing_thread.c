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
struct perf_thread_map {int nr; } ;
struct TYPE_2__ {scalar_t__ system_wide; } ;
struct evsel {TYPE_1__ core; int /*<<< orphan*/  ignore_missing_thread; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int ESRCH ; 
 int /*<<< orphan*/  perf_thread_map__pid (struct perf_thread_map*,int) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ thread_map__remove (struct perf_thread_map*,int) ; 
 scalar_t__ update_fds (struct evsel*,int,int,int,int) ; 

__attribute__((used)) static bool ignore_missing_thread(struct evsel *evsel,
				  int nr_cpus, int cpu,
				  struct perf_thread_map *threads,
				  int thread, int err)
{
	pid_t ignore_pid = perf_thread_map__pid(threads, thread);

	if (!evsel->ignore_missing_thread)
		return false;

	/* The system wide setup does not work with threads. */
	if (evsel->core.system_wide)
		return false;

	/* The -ESRCH is perf event syscall errno for pid's not found. */
	if (err != -ESRCH)
		return false;

	/* If there's only one thread, let it fail. */
	if (threads->nr == 1)
		return false;

	/*
	 * We should remove fd for missing_thread first
	 * because thread_map__remove() will decrease threads->nr.
	 */
	if (update_fds(evsel, nr_cpus, cpu, threads->nr, thread))
		return false;

	if (thread_map__remove(threads, thread))
		return false;

	pr_warning("WARNING: Ignored open failure for pid %d\n",
		   ignore_pid);
	return true;
}