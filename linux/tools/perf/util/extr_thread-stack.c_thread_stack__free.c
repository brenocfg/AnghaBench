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
struct thread_stack {unsigned int arr_sz; } ;
struct thread {struct thread_stack* ts; } ;

/* Variables and functions */
 int /*<<< orphan*/  __thread_stack__free (struct thread*,struct thread_stack*) ; 
 int /*<<< orphan*/  zfree (struct thread_stack**) ; 

void thread_stack__free(struct thread *thread)
{
	struct thread_stack *ts = thread->ts;
	unsigned int pos;

	if (ts) {
		for (pos = 0; pos < ts->arr_sz; pos++)
			__thread_stack__free(thread, ts + pos);
		zfree(&thread->ts);
	}
}