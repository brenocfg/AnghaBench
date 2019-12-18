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
struct trace_event_file {int dummy; } ;

/* Variables and functions */
 int __ftrace_event_enable_disable (struct trace_event_file*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ftrace_event_enable_disable(struct trace_event_file *file,
				       int enable)
{
	return __ftrace_event_enable_disable(file, enable, 0);
}