#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  union perf_event {int dummy; } perf_event ;
struct mmap {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* cb ) (union perf_event*,int /*<<< orphan*/ ) ;} ;
struct evsel {TYPE_3__ side_band; } ;
struct TYPE_5__ {int nr_mmaps; } ;
struct TYPE_4__ {scalar_t__ done; } ;
struct evlist {struct mmap* mmap; TYPE_2__ core; TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLONE_FS ; 
 int /*<<< orphan*/  evlist__poll (struct evlist*,int) ; 
 struct evsel* perf_evlist__event2evsel (struct evlist*,union perf_event*) ; 
 int /*<<< orphan*/  perf_mmap__consume (struct mmap*) ; 
 int /*<<< orphan*/  perf_mmap__read_done (struct mmap*) ; 
 union perf_event* perf_mmap__read_event (struct mmap*) ; 
 scalar_t__ perf_mmap__read_init (struct mmap*) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 int /*<<< orphan*/  stub1 (union perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unshare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *perf_evlist__poll_thread(void *arg)
{
	struct evlist *evlist = arg;
	bool draining = false;
	int i, done = 0;
	/*
	 * In order to read symbols from other namespaces perf to needs to call
	 * setns(2).  This isn't permitted if the struct_fs has multiple users.
	 * unshare(2) the fs so that we may continue to setns into namespaces
	 * that we're observing when, for instance, reading the build-ids at
	 * the end of a 'perf record' session.
	 */
	unshare(CLONE_FS);

	while (!done) {
		bool got_data = false;

		if (evlist->thread.done)
			draining = true;

		if (!draining)
			evlist__poll(evlist, 1000);

		for (i = 0; i < evlist->core.nr_mmaps; i++) {
			struct mmap *map = &evlist->mmap[i];
			union perf_event *event;

			if (perf_mmap__read_init(map))
				continue;
			while ((event = perf_mmap__read_event(map)) != NULL) {
				struct evsel *evsel = perf_evlist__event2evsel(evlist, event);

				if (evsel && evsel->side_band.cb)
					evsel->side_band.cb(event, evsel->side_band.data);
				else
					pr_warning("cannot locate proper evsel for the side band event\n");

				perf_mmap__consume(map);
				got_data = true;
			}
			perf_mmap__read_done(map);
		}

		if (draining && !got_data)
			break;
	}
	return NULL;
}