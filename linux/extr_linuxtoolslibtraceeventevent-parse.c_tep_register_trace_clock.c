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
struct tep_handle {int /*<<< orphan*/  trace_clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  strdup (char const*) ; 

int tep_register_trace_clock(struct tep_handle *pevent, const char *trace_clock)
{
	pevent->trace_clock = strdup(trace_clock);
	if (!pevent->trace_clock) {
		errno = ENOMEM;
		return -1;
	}
	return 0;
}