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
typedef  scalar_t__ u64 ;
struct thread_stack {scalar_t__ trace_nr; } ;
struct thread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __thread_stack__flush (struct thread*,struct thread_stack*) ; 
 struct thread_stack* thread__stack (struct thread*,int) ; 

void thread_stack__set_trace_nr(struct thread *thread, int cpu, u64 trace_nr)
{
	struct thread_stack *ts = thread__stack(thread, cpu);

	if (!ts)
		return;

	if (trace_nr != ts->trace_nr) {
		if (ts->trace_nr)
			__thread_stack__flush(thread, ts);
		ts->trace_nr = trace_nr;
	}
}