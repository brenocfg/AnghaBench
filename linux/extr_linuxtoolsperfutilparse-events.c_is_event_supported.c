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
typedef  int /*<<< orphan*/  u8 ;
struct thread_map {int dummy; } ;
struct TYPE_2__ {int exclude_kernel; } ;
struct perf_evsel {TYPE_1__ attr; } ;
struct perf_event_attr {unsigned int config; int disabled; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  perf_evsel__delete (struct perf_evsel*) ; 
 struct perf_evsel* perf_evsel__new (struct perf_event_attr*) ; 
 int perf_evsel__open (struct perf_evsel*,int /*<<< orphan*/ *,struct thread_map*) ; 
 struct thread_map* thread_map__new_by_tid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_map__put (struct thread_map*) ; 

__attribute__((used)) static bool is_event_supported(u8 type, unsigned config)
{
	bool ret = true;
	int open_return;
	struct perf_evsel *evsel;
	struct perf_event_attr attr = {
		.type = type,
		.config = config,
		.disabled = 1,
	};
	struct thread_map *tmap = thread_map__new_by_tid(0);

	if (tmap == NULL)
		return false;

	evsel = perf_evsel__new(&attr);
	if (evsel) {
		open_return = perf_evsel__open(evsel, NULL, tmap);
		ret = open_return >= 0;

		if (open_return == -EACCES) {
			/*
			 * This happens if the paranoid value
			 * /proc/sys/kernel/perf_event_paranoid is set to 2
			 * Re-run with exclude_kernel set; we don't do that
			 * by default as some ARM machines do not support it.
			 *
			 */
			evsel->attr.exclude_kernel = 1;
			ret = perf_evsel__open(evsel, NULL, tmap) >= 0;
		}
		perf_evsel__delete(evsel);
	}

	thread_map__put(tmap);
	return ret;
}