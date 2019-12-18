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
struct trace_event_call {int /*<<< orphan*/  class; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int __trace_define_field (struct list_head*,char const*,char const*,int,int,int,int) ; 
 struct list_head* trace_get_fields (struct trace_event_call*) ; 

int trace_define_field(struct trace_event_call *call, const char *type,
		       const char *name, int offset, int size, int is_signed,
		       int filter_type)
{
	struct list_head *head;

	if (WARN_ON(!call->class))
		return 0;

	head = trace_get_fields(call);
	return __trace_define_field(head, type, name, offset, size,
				    is_signed, filter_type);
}