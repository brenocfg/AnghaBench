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
 int /*<<< orphan*/  write_int_to (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_pid_to (char*,char*) ; 

void trace_me(void)
{
/* tracing events dir */
#define TED "/sys/kernel/debug/tracing/events/"
/*
	write_pid_to("common_pid=", TED "signal/filter");
	write_pid_to("common_pid=", TED "exceptions/filter");
	write_int_to("", TED "signal/enable", 1);
	write_int_to("", TED "exceptions/enable", 1);
*/
	write_pid_to("", "/sys/kernel/debug/tracing/set_ftrace_pid");
	write_int_to("", "/sys/kernel/debug/tracing/trace", 0);
}