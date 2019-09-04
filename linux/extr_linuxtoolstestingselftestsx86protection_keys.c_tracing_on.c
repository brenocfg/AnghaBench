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

void tracing_on(void)
{
#if CONTROL_TRACING > 0
#define TRACEDIR "/sys/kernel/debug/tracing"
	char pidstr[32];

	if (!tracing_root_ok())
		return;

	sprintf(pidstr, "%d", getpid());
	cat_into_file("0", TRACEDIR "/tracing_on");
	cat_into_file("\n", TRACEDIR "/trace");
	if (1) {
		cat_into_file("function_graph", TRACEDIR "/current_tracer");
		cat_into_file("1", TRACEDIR "/options/funcgraph-proc");
	} else {
		cat_into_file("nop", TRACEDIR "/current_tracer");
	}
	cat_into_file(pidstr, TRACEDIR "/set_ftrace_pid");
	cat_into_file("1", TRACEDIR "/tracing_on");
	dprintf1("enabled tracing\n");
#endif
}