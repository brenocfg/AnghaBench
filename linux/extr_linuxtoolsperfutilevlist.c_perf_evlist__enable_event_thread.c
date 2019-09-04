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
struct perf_evsel {int /*<<< orphan*/  fd; } ;
struct perf_evlist {int /*<<< orphan*/  cpus; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FD (struct perf_evsel*,int,int) ; 
 int /*<<< orphan*/  PERF_EVENT_IOC_ENABLE ; 
 int cpu_map__nr (int /*<<< orphan*/ ) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int perf_evlist__enable_event_thread(struct perf_evlist *evlist,
					    struct perf_evsel *evsel,
					    int thread)
{
	int cpu;
	int nr_cpus = cpu_map__nr(evlist->cpus);

	if (!evsel->fd)
		return -EINVAL;

	for (cpu = 0; cpu < nr_cpus; cpu++) {
		int err = ioctl(FD(evsel, cpu, thread), PERF_EVENT_IOC_ENABLE, 0);
		if (err)
			return err;
	}
	return 0;
}