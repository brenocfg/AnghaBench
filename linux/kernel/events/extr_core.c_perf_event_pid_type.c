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
typedef  int u32 ;
struct task_struct {int dummy; } ;
struct perf_event {int /*<<< orphan*/  ns; struct perf_event* parent; } ;
typedef  enum pid_type { ____Placeholder_pid_type } pid_type ;

/* Variables and functions */
 int __task_pid_nr_ns (struct task_struct*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pid_alive (struct task_struct*) ; 

__attribute__((used)) static u32 perf_event_pid_type(struct perf_event *event, struct task_struct *p,
				enum pid_type type)
{
	u32 nr;
	/*
	 * only top level events have the pid namespace they were created in
	 */
	if (event->parent)
		event = event->parent;

	nr = __task_pid_nr_ns(p, type, event->ns);
	/* avoid -1 if it is idle thread or runs in another ns */
	if (!nr && !pid_alive(p))
		nr = -1;
	return nr;
}