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
struct trace_probe {int dummy; } ;
struct trace_event_call {char* print_fmt; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int __set_print_fmt (struct trace_probe*,char*,int,int) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct trace_event_call* trace_probe_event_call (struct trace_probe*) ; 

int traceprobe_set_print_fmt(struct trace_probe *tp, bool is_return)
{
	struct trace_event_call *call = trace_probe_event_call(tp);
	int len;
	char *print_fmt;

	/* First: called with 0 length to calculate the needed length */
	len = __set_print_fmt(tp, NULL, 0, is_return);
	print_fmt = kmalloc(len + 1, GFP_KERNEL);
	if (!print_fmt)
		return -ENOMEM;

	/* Second: actually write the @print_fmt */
	__set_print_fmt(tp, print_fmt, len + 1, is_return);
	call->print_fmt = print_fmt;

	return 0;
}