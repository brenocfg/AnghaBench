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
struct call_return_processor {int dummy; } ;

/* Variables and functions */
 struct thread_stack* calloc (unsigned int,int) ; 
 int /*<<< orphan*/  memcpy (struct thread_stack*,struct thread_stack*,unsigned int) ; 
 unsigned int roundup_pow_of_two (int) ; 
 scalar_t__ thread_stack__init (struct thread_stack*,struct thread*,struct call_return_processor*) ; 
 scalar_t__ thread_stack__per_cpu (struct thread*) ; 
 int /*<<< orphan*/  zfree (struct thread_stack**) ; 

__attribute__((used)) static struct thread_stack *thread_stack__new(struct thread *thread, int cpu,
					      struct call_return_processor *crp)
{
	struct thread_stack *ts = thread->ts, *new_ts;
	unsigned int old_sz = ts ? ts->arr_sz : 0;
	unsigned int new_sz = 1;

	if (thread_stack__per_cpu(thread) && cpu > 0)
		new_sz = roundup_pow_of_two(cpu + 1);

	if (!ts || new_sz > old_sz) {
		new_ts = calloc(new_sz, sizeof(*ts));
		if (!new_ts)
			return NULL;
		if (ts)
			memcpy(new_ts, ts, old_sz * sizeof(*ts));
		new_ts->arr_sz = new_sz;
		zfree(&thread->ts);
		thread->ts = new_ts;
		ts = new_ts;
	}

	if (thread_stack__per_cpu(thread) && cpu > 0 &&
	    (unsigned int)cpu < ts->arr_sz)
		ts += cpu;

	if (!ts->stack &&
	    thread_stack__init(ts, thread, crp))
		return NULL;

	return ts;
}