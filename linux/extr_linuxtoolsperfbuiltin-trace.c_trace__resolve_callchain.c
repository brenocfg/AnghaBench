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
struct trace {int max_stack; int /*<<< orphan*/  host; } ;
struct perf_sample {int dummy; } ;
struct TYPE_2__ {int sample_max_stack; } ;
struct perf_evsel {TYPE_1__ attr; } ;
struct callchain_cursor {int dummy; } ;
struct addr_location {int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 scalar_t__ machine__resolve (int /*<<< orphan*/ ,struct addr_location*,struct perf_sample*) ; 
 scalar_t__ thread__resolve_callchain (int /*<<< orphan*/ ,struct callchain_cursor*,struct perf_evsel*,struct perf_sample*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int trace__resolve_callchain(struct trace *trace, struct perf_evsel *evsel,
				    struct perf_sample *sample,
				    struct callchain_cursor *cursor)
{
	struct addr_location al;
	int max_stack = evsel->attr.sample_max_stack ?
			evsel->attr.sample_max_stack :
			trace->max_stack;

	if (machine__resolve(trace->host, &al, sample) < 0 ||
	    thread__resolve_callchain(al.thread, cursor, evsel, sample, NULL, NULL, max_stack))
		return -1;

	return 0;
}