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
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static bool is_timestamp_in_us(char *trace_clock, bool use_trace_clock)
{
	if (!use_trace_clock)
		return true;

	if (!strcmp(trace_clock, "local") || !strcmp(trace_clock, "global")
	    || !strcmp(trace_clock, "uptime") || !strcmp(trace_clock, "perf"))
		return true;

	/* trace_clock is setting in tsc or counter mode */
	return false;
}