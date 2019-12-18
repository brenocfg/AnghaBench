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
struct perf_thread_map {int dummy; } ;
struct perf_evsel {int dummy; } ;
struct perf_event_attr {int disabled; int /*<<< orphan*/  config; int /*<<< orphan*/  type; } ;
struct perf_counts_values {scalar_t__ val; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_COUNT_SW_TASK_CLOCK ; 
 int /*<<< orphan*/  PERF_TYPE_SOFTWARE ; 
 int /*<<< orphan*/  __T (char*,int) ; 
 int /*<<< orphan*/  perf_evsel__close (struct perf_evsel*) ; 
 int /*<<< orphan*/  perf_evsel__delete (struct perf_evsel*) ; 
 int perf_evsel__disable (struct perf_evsel*) ; 
 int perf_evsel__enable (struct perf_evsel*) ; 
 struct perf_evsel* perf_evsel__new (struct perf_event_attr*) ; 
 int perf_evsel__open (struct perf_evsel*,int /*<<< orphan*/ *,struct perf_thread_map*) ; 
 int /*<<< orphan*/  perf_evsel__read (struct perf_evsel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct perf_counts_values*) ; 
 struct perf_thread_map* perf_thread_map__new_dummy () ; 
 int /*<<< orphan*/  perf_thread_map__put (struct perf_thread_map*) ; 
 int /*<<< orphan*/  perf_thread_map__set_pid (struct perf_thread_map*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_stat_thread_enable(void)
{
	struct perf_counts_values counts = { .val = 0 };
	struct perf_thread_map *threads;
	struct perf_evsel *evsel;
	struct perf_event_attr attr = {
		.type	  = PERF_TYPE_SOFTWARE,
		.config	  = PERF_COUNT_SW_TASK_CLOCK,
		.disabled = 1,
	};
	int err;

	threads = perf_thread_map__new_dummy();
	__T("failed to create threads", threads);

	perf_thread_map__set_pid(threads, 0, 0);

	evsel = perf_evsel__new(&attr);
	__T("failed to create evsel", evsel);

	err = perf_evsel__open(evsel, NULL, threads);
	__T("failed to open evsel", err == 0);

	perf_evsel__read(evsel, 0, 0, &counts);
	__T("failed to read value for evsel", counts.val == 0);

	err = perf_evsel__enable(evsel);
	__T("failed to enable evsel", err == 0);

	perf_evsel__read(evsel, 0, 0, &counts);
	__T("failed to read value for evsel", counts.val != 0);

	err = perf_evsel__disable(evsel);
	__T("failed to enable evsel", err == 0);

	perf_evsel__close(evsel);
	perf_evsel__delete(evsel);

	perf_thread_map__put(threads);
	return 0;
}