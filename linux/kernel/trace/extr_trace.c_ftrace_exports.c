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
struct trace_export {int /*<<< orphan*/  next; } ;
struct ring_buffer_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ftrace_exports_list ; 
 int /*<<< orphan*/  preempt_disable_notrace () ; 
 int /*<<< orphan*/  preempt_enable_notrace () ; 
 struct trace_export* rcu_dereference_raw_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_process_export (struct trace_export*,struct ring_buffer_event*) ; 

__attribute__((used)) static void ftrace_exports(struct ring_buffer_event *event)
{
	struct trace_export *export;

	preempt_disable_notrace();

	export = rcu_dereference_raw_check(ftrace_exports_list);
	while (export) {
		trace_process_export(export, event);
		export = rcu_dereference_raw_check(export->next);
	}

	preempt_enable_notrace();
}