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
struct trace_event_call {struct syscall_metadata* data; } ;
struct list_head {int dummy; } ;
struct syscall_metadata {struct list_head enter_fields; } ;

/* Variables and functions */

__attribute__((used)) static struct list_head *
syscall_get_enter_fields(struct trace_event_call *call)
{
	struct syscall_metadata *entry = call->data;

	return &entry->enter_fields;
}