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
struct trace_event_call {TYPE_1__* class; } ;
struct list_head {int dummy; } ;
struct TYPE_2__ {struct list_head* (* get_fields ) (struct trace_event_call*) ;struct list_head fields; } ;

/* Variables and functions */
 struct list_head* stub1 (struct trace_event_call*) ; 

__attribute__((used)) static struct list_head *
trace_get_fields(struct trace_event_call *event_call)
{
	if (!event_call->class->get_fields)
		return &event_call->class->fields;
	return event_call->class->get_fields(event_call);
}