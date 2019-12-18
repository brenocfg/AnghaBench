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
struct trace_event_call {int dummy; } ;
struct trace_array {int /*<<< orphan*/  event_dir; } ;

/* Variables and functions */
 int ENOMEM ; 
 int event_create_dir (int /*<<< orphan*/ ,struct trace_event_file*) ; 
 struct trace_event_file* trace_create_new_event (struct trace_event_call*,struct trace_array*) ; 

__attribute__((used)) static int
__trace_add_new_event(struct trace_event_call *call, struct trace_array *tr)
{
	struct trace_event_file *file;

	file = trace_create_new_event(call, tr);
	if (!file)
		return -ENOMEM;

	return event_create_dir(tr->event_dir, file);
}