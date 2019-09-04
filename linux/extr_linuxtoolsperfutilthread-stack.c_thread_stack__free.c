#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thread {TYPE_1__* ts; } ;
struct TYPE_3__ {struct TYPE_3__* stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  __thread_stack__flush (struct thread*,TYPE_1__*) ; 
 int /*<<< orphan*/  zfree (TYPE_1__**) ; 

void thread_stack__free(struct thread *thread)
{
	if (thread->ts) {
		__thread_stack__flush(thread, thread->ts);
		zfree(&thread->ts->stack);
		zfree(&thread->ts);
	}
}