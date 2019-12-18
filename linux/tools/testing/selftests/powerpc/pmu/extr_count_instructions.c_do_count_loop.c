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
typedef  int u64 ;
struct TYPE_2__ {int value; } ;
struct event {TYPE_1__ result; } ;
typedef  int s64 ;

/* Variables and functions */
 int /*<<< orphan*/  PR_TASK_PERF_EVENTS_DISABLE ; 
 int /*<<< orphan*/  PR_TASK_PERF_EVENTS_ENABLE ; 
 int /*<<< orphan*/  event_read (struct event*) ; 
 int /*<<< orphan*/  event_report (struct event*) ; 
 int /*<<< orphan*/  event_reset (struct event*) ; 
 int /*<<< orphan*/  prctl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int /*<<< orphan*/  thirty_two_instruction_loop (int) ; 

__attribute__((used)) static int do_count_loop(struct event *events, u64 instructions,
			 u64 overhead, bool report)
{
	s64 difference, expected;
	double percentage;

	prctl(PR_TASK_PERF_EVENTS_ENABLE);

	/* Run for 1M instructions */
	thirty_two_instruction_loop(instructions >> 5);

	prctl(PR_TASK_PERF_EVENTS_DISABLE);

	event_read(&events[0]);
	event_read(&events[1]);

	expected = instructions + overhead;
	difference = events[0].result.value - expected;
	percentage = (double)difference / events[0].result.value * 100;

	if (report) {
		event_report(&events[0]);
		event_report(&events[1]);

		printf("Looped for %llu instructions, overhead %llu\n", instructions, overhead);
		printf("Expected %llu\n", expected);
		printf("Actual   %llu\n", events[0].result.value);
		printf("Delta    %lld, %f%%\n", difference, percentage);
	}

	event_reset(&events[0]);
	event_reset(&events[1]);

	if (difference < 0)
		difference = -difference;

	/* Tolerate a difference below 0.0001 % */
	difference *= 10000 * 100;
	if (difference / events[0].result.value)
		return -1;

	return 0;
}