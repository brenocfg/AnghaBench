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
typedef  int /*<<< orphan*/  u64 ;
struct thread_stack {int /*<<< orphan*/  cnt; } ;
struct thread {int dummy; } ;
struct perf_sample {int /*<<< orphan*/  time; } ;

/* Variables and functions */
 int thread_stack__call_return (struct thread*,struct thread_stack*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ thread_stack__in_kernel (struct thread_stack*) ; 

__attribute__((used)) static int thread_stack__pop_ks(struct thread *thread, struct thread_stack *ts,
				struct perf_sample *sample, u64 ref)
{
	u64 tm = sample->time;
	int err;

	/* Return to userspace, so pop all kernel addresses */
	while (thread_stack__in_kernel(ts)) {
		err = thread_stack__call_return(thread, ts, --ts->cnt,
						tm, ref, true);
		if (err)
			return err;
	}

	return 0;
}