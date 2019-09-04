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
struct thread_map {int dummy; } ;
struct TYPE_2__ {int disabled; } ;
struct perf_evsel {TYPE_1__ attr; } ;
struct perf_evlist {int dummy; } ;

/* Variables and functions */
 int TEST_FAIL ; 
 int TEST_OK ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int /*<<< orphan*/  getpid () ; 
 struct perf_evsel* perf_evlist__last (struct perf_evlist*) ; 
 scalar_t__ perf_evsel__enable (struct perf_evsel*) ; 
 int perf_evsel__open_per_thread (struct perf_evsel*,struct thread_map*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 struct thread_map* thread_map__new (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_map__put (struct thread_map*) ; 

__attribute__((used)) static int attach__current_disabled(struct perf_evlist *evlist)
{
	struct perf_evsel *evsel = perf_evlist__last(evlist);
	struct thread_map *threads;
	int err;

	pr_debug("attaching to current thread as disabled\n");

	threads = thread_map__new(-1, getpid(), UINT_MAX);
	if (threads == NULL) {
		pr_debug("thread_map__new\n");
		return -1;
	}

	evsel->attr.disabled = 1;

	err = perf_evsel__open_per_thread(evsel, threads);
	if (err) {
		pr_debug("Failed to open event cpu-clock:u\n");
		return err;
	}

	thread_map__put(threads);
	return perf_evsel__enable(evsel) == 0 ? TEST_OK : TEST_FAIL;
}