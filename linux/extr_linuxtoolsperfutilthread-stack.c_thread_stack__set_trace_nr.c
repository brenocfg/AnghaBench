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
typedef  scalar_t__ u64 ;
struct thread {TYPE_1__* ts; } ;
struct TYPE_2__ {scalar_t__ trace_nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  __thread_stack__flush (struct thread*,TYPE_1__*) ; 

void thread_stack__set_trace_nr(struct thread *thread, u64 trace_nr)
{
	if (!thread || !thread->ts)
		return;

	if (trace_nr != thread->ts->trace_nr) {
		if (thread->ts->trace_nr)
			__thread_stack__flush(thread, thread->ts);
		thread->ts->trace_nr = trace_nr;
	}
}