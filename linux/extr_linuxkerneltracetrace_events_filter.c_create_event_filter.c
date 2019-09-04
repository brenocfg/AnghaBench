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
struct trace_event_call {int dummy; } ;
struct event_filter {int dummy; } ;

/* Variables and functions */
 int create_filter (struct trace_event_call*,char*,int,struct event_filter**) ; 

int create_event_filter(struct trace_event_call *call,
			char *filter_str, bool set_str,
			struct event_filter **filterp)
{
	return create_filter(call, filter_str, set_str, filterp);
}