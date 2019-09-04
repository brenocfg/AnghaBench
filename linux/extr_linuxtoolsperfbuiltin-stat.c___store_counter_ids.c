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

/* Variables and functions */
 int FD (struct perf_evsel*,int,int) ; 
 int /*<<< orphan*/  evsel_list ; 
 scalar_t__ perf_evlist__id_add_fd (int /*<<< orphan*/ ,struct perf_evsel*,int,int,int) ; 
 int xyarray__max_x (int /*<<< orphan*/ ) ; 
 int xyarray__max_y (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __store_counter_ids(struct perf_evsel *counter)
{
	int cpu, thread;

	for (cpu = 0; cpu < xyarray__max_x(counter->fd); cpu++) {
		for (thread = 0; thread < xyarray__max_y(counter->fd);
		     thread++) {
			int fd = FD(counter, cpu, thread);

			if (perf_evlist__id_add_fd(evsel_list, counter,
						   cpu, thread, fd) < 0)
				return -1;
		}
	}

	return 0;
}