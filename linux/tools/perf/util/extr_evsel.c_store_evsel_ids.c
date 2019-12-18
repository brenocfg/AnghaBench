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
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;
struct evsel {TYPE_1__ core; } ;
struct evlist {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int FD (struct evsel*,int,int) ; 
 scalar_t__ perf_evlist__id_add_fd (int /*<<< orphan*/ *,TYPE_1__*,int,int,int) ; 
 int xyarray__max_x (int /*<<< orphan*/ ) ; 
 int xyarray__max_y (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int store_evsel_ids(struct evsel *evsel, struct evlist *evlist)
{
	int cpu, thread;

	for (cpu = 0; cpu < xyarray__max_x(evsel->core.fd); cpu++) {
		for (thread = 0; thread < xyarray__max_y(evsel->core.fd);
		     thread++) {
			int fd = FD(evsel, cpu, thread);

			if (perf_evlist__id_add_fd(&evlist->core, &evsel->core,
						   cpu, thread, fd) < 0)
				return -1;
		}
	}

	return 0;
}