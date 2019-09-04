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
struct thread_stack {unsigned long long kernel_start; struct call_return_processor* crp; } ;
struct thread {TYPE_1__* mg; } ;
struct call_return_processor {int dummy; } ;
struct TYPE_2__ {scalar_t__ machine; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct thread_stack*) ; 
 unsigned long long machine__kernel_start (scalar_t__) ; 
 scalar_t__ thread_stack__grow (struct thread_stack*) ; 
 struct thread_stack* zalloc (int) ; 

__attribute__((used)) static struct thread_stack *thread_stack__new(struct thread *thread,
					      struct call_return_processor *crp)
{
	struct thread_stack *ts;

	ts = zalloc(sizeof(struct thread_stack));
	if (!ts)
		return NULL;

	if (thread_stack__grow(ts)) {
		free(ts);
		return NULL;
	}

	if (thread->mg && thread->mg->machine)
		ts->kernel_start = machine__kernel_start(thread->mg->machine);
	else
		ts->kernel_start = 1ULL << 63;
	ts->crp = crp;

	return ts;
}