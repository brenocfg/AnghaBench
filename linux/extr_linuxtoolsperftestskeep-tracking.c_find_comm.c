#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  comm; scalar_t__ tid; scalar_t__ pid; } ;
struct TYPE_3__ {scalar_t__ type; } ;
union perf_event {TYPE_2__ comm; TYPE_1__ header; } ;
struct perf_mmap {int dummy; } ;
struct perf_evlist {int nr_mmaps; struct perf_mmap* mmap; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 scalar_t__ PERF_RECORD_COMM ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  perf_mmap__consume (struct perf_mmap*) ; 
 int /*<<< orphan*/  perf_mmap__read_done (struct perf_mmap*) ; 
 union perf_event* perf_mmap__read_event (struct perf_mmap*) ; 
 scalar_t__ perf_mmap__read_init (struct perf_mmap*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int find_comm(struct perf_evlist *evlist, const char *comm)
{
	union perf_event *event;
	struct perf_mmap *md;
	int i, found;

	found = 0;
	for (i = 0; i < evlist->nr_mmaps; i++) {
		md = &evlist->mmap[i];
		if (perf_mmap__read_init(md) < 0)
			continue;
		while ((event = perf_mmap__read_event(md)) != NULL) {
			if (event->header.type == PERF_RECORD_COMM &&
			    (pid_t)event->comm.pid == getpid() &&
			    (pid_t)event->comm.tid == getpid() &&
			    strcmp(event->comm.comm, comm) == 0)
				found += 1;
			perf_mmap__consume(md);
		}
		perf_mmap__read_done(md);
	}
	return found;
}