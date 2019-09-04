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
typedef  union perf_event {int dummy; } perf_event ;
struct state {int dummy; } ;
struct perf_mmap {int dummy; } ;
struct perf_evlist {int nr_mmaps; struct perf_mmap* mmap; } ;
struct machine {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_mmap__consume (struct perf_mmap*) ; 
 int /*<<< orphan*/  perf_mmap__read_done (struct perf_mmap*) ; 
 union perf_event* perf_mmap__read_event (struct perf_mmap*) ; 
 scalar_t__ perf_mmap__read_init (struct perf_mmap*) ; 
 int process_event (struct machine*,struct perf_evlist*,union perf_event*,struct state*) ; 

__attribute__((used)) static int process_events(struct machine *machine, struct perf_evlist *evlist,
			  struct state *state)
{
	union perf_event *event;
	struct perf_mmap *md;
	int i, ret;

	for (i = 0; i < evlist->nr_mmaps; i++) {
		md = &evlist->mmap[i];
		if (perf_mmap__read_init(md) < 0)
			continue;

		while ((event = perf_mmap__read_event(md)) != NULL) {
			ret = process_event(machine, evlist, event, state);
			perf_mmap__consume(md);
			if (ret < 0)
				return ret;
		}
		perf_mmap__read_done(md);
	}
	return 0;
}