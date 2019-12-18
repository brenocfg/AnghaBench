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
struct perf_record_stat {int /*<<< orphan*/  thread; int /*<<< orphan*/  cpu; int /*<<< orphan*/  id; int /*<<< orphan*/  run; int /*<<< orphan*/  ena; int /*<<< orphan*/  val; } ;
union perf_event {struct perf_record_stat stat; } ;
struct perf_session {int /*<<< orphan*/  evlist; } ;
struct perf_counts_values {int /*<<< orphan*/  run; int /*<<< orphan*/  ena; int /*<<< orphan*/  val; } ;
struct evsel {int supported; int /*<<< orphan*/  counts; } ;

/* Variables and functions */
 int EINVAL ; 
 struct perf_counts_values* perf_counts (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct evsel* perf_evlist__id2evsel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int perf_event__process_stat_event(struct perf_session *session,
				   union perf_event *event)
{
	struct perf_counts_values count;
	struct perf_record_stat *st = &event->stat;
	struct evsel *counter;

	count.val = st->val;
	count.ena = st->ena;
	count.run = st->run;

	counter = perf_evlist__id2evsel(session->evlist, st->id);
	if (!counter) {
		pr_err("Failed to resolve counter for stat event.\n");
		return -EINVAL;
	}

	*perf_counts(counter->counts, st->cpu, st->thread) = count;
	counter->supported = true;
	return 0;
}