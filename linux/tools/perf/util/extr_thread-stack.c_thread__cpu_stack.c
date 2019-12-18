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
struct thread_stack {unsigned int arr_sz; int /*<<< orphan*/  stack; } ;
struct thread {struct thread_stack* ts; } ;

/* Variables and functions */

__attribute__((used)) static struct thread_stack *thread__cpu_stack(struct thread *thread, int cpu)
{
	struct thread_stack *ts = thread->ts;

	if (cpu < 0)
		cpu = 0;

	if (!ts || (unsigned int)cpu >= ts->arr_sz)
		return NULL;

	ts += cpu;

	if (!ts->stack)
		return NULL;

	return ts;
}