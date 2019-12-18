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
typedef  void* u64 ;
struct timechart {int dummy; } ;
struct perf_sample {int /*<<< orphan*/  time; int /*<<< orphan*/  cpu; } ;
struct evsel {int dummy; } ;

/* Variables and functions */
 void* perf_evsel__intval (struct evsel*,struct perf_sample*,char*) ; 
 int /*<<< orphan*/  sched_switch (struct timechart*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,void*,char const*) ; 

__attribute__((used)) static int
process_sample_sched_switch(struct timechart *tchart,
			    struct evsel *evsel,
			    struct perf_sample *sample,
			    const char *backtrace)
{
	int prev_pid = perf_evsel__intval(evsel, sample, "prev_pid");
	int next_pid = perf_evsel__intval(evsel, sample, "next_pid");
	u64 prev_state = perf_evsel__intval(evsel, sample, "prev_state");

	sched_switch(tchart, sample->cpu, sample->time, prev_pid, next_pid,
		     prev_state, backtrace);
	return 0;
}