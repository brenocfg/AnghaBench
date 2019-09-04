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

/* Variables and functions */
 int USEC_PER_MSEC ; 
 int /*<<< orphan*/  evsel_list ; 
 int initial_delay ; 
 int /*<<< orphan*/  perf_evlist__enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target ; 
 int /*<<< orphan*/  target__none (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static void enable_counters(void)
{
	if (initial_delay)
		usleep(initial_delay * USEC_PER_MSEC);

	/*
	 * We need to enable counters only if:
	 * - we don't have tracee (attaching to task or cpu)
	 * - we have initial delay configured
	 */
	if (!target__none(&target) || initial_delay)
		perf_evlist__enable(evsel_list);
}