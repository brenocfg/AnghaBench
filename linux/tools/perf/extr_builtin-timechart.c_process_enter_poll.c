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
struct timechart {int dummy; } ;
struct perf_sample {int /*<<< orphan*/  time; int /*<<< orphan*/  tid; } ;
struct evsel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOTYPE_POLL ; 
 long perf_evsel__intval (struct evsel*,struct perf_sample*,char*) ; 
 int pid_begin_io_sample (struct timechart*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 

__attribute__((used)) static int
process_enter_poll(struct timechart *tchart,
		   struct evsel *evsel,
		   struct perf_sample *sample)
{
	long fd = perf_evsel__intval(evsel, sample, "fd");
	return pid_begin_io_sample(tchart, sample->tid, IOTYPE_POLL,
				   sample->time, fd);
}