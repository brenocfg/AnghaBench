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
typedef  int /*<<< orphan*/  u64 ;
struct event {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_IF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PERF_COUNT_HW_CPU_CYCLES ; 
 int /*<<< orphan*/  PERF_COUNT_HW_INSTRUCTIONS ; 
 int /*<<< orphan*/  determine_overhead (struct event*) ; 
 int /*<<< orphan*/  do_count_loop (struct event*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  event_close (struct event*) ; 
 scalar_t__ event_open (struct event*) ; 
 scalar_t__ event_open_with_group (struct event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_event (struct event*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int test_body(void)
{
	struct event events[2];
	u64 overhead;

	setup_event(&events[0], PERF_COUNT_HW_INSTRUCTIONS, "instructions");
	setup_event(&events[1], PERF_COUNT_HW_CPU_CYCLES, "cycles");

	if (event_open(&events[0])) {
		perror("perf_event_open");
		return -1;
	}

	if (event_open_with_group(&events[1], events[0].fd)) {
		perror("perf_event_open");
		return -1;
	}

	overhead = determine_overhead(events);
	printf("Overhead of null loop: %llu instructions\n", overhead);

	/* Run for 1Mi instructions */
	FAIL_IF(do_count_loop(events, 1000000, overhead, true));

	/* Run for 10Mi instructions */
	FAIL_IF(do_count_loop(events, 10000000, overhead, true));

	/* Run for 100Mi instructions */
	FAIL_IF(do_count_loop(events, 100000000, overhead, true));

	/* Run for 1Bi instructions */
	FAIL_IF(do_count_loop(events, 1000000000, overhead, true));

	/* Run for 16Bi instructions */
	FAIL_IF(do_count_loop(events, 16000000000, overhead, true));

	/* Run for 64Bi instructions */
	FAIL_IF(do_count_loop(events, 64000000000, overhead, true));

	event_close(&events[0]);
	event_close(&events[1]);

	return 0;
}