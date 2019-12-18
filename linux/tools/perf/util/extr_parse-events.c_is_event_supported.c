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
typedef  int /*<<< orphan*/  u8 ;
struct perf_thread_map {int dummy; } ;
struct perf_event_attr {unsigned int config; int disabled; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int exclude_kernel; } ;
struct TYPE_4__ {TYPE_1__ attr; } ;
struct evsel {TYPE_2__ core; } ;

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  evsel__delete (struct evsel*) ; 
 struct evsel* evsel__new (struct perf_event_attr*) ; 
 int evsel__open (struct evsel*,int /*<<< orphan*/ *,struct perf_thread_map*) ; 
 int /*<<< orphan*/  perf_thread_map__put (struct perf_thread_map*) ; 
 struct perf_thread_map* thread_map__new_by_tid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_event_supported(u8 type, unsigned config)
{
	bool ret = true;
	int open_return;
	struct evsel *evsel;
	struct perf_event_attr attr = {
		.type = type,
		.config = config,
		.disabled = 1,
	};
	struct perf_thread_map *tmap = thread_map__new_by_tid(0);

	if (tmap == NULL)
		return false;

	evsel = evsel__new(&attr);
	if (evsel) {
		open_return = evsel__open(evsel, NULL, tmap);
		ret = open_return >= 0;

		if (open_return == -EACCES) {
			/*
			 * This happens if the paranoid value
			 * /proc/sys/kernel/perf_event_paranoid is set to 2
			 * Re-run with exclude_kernel set; we don't do that
			 * by default as some ARM machines do not support it.
			 *
			 */
			evsel->core.attr.exclude_kernel = 1;
			ret = evsel__open(evsel, NULL, tmap) >= 0;
		}
		evsel__delete(evsel);
	}

	perf_thread_map__put(tmap);
	return ret;
}