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
typedef  int /*<<< orphan*/  u64 ;
struct thread_stack_entry {TYPE_1__* cp; } ;
struct thread_stack {int cnt; struct thread_stack_entry* stack; } ;
struct thread {int dummy; } ;
struct TYPE_2__ {scalar_t__ ip; int /*<<< orphan*/ * sym; } ;

/* Variables and functions */
 int thread_stack__call_return (struct thread*,struct thread_stack*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int thread_stack__trace_begin(struct thread *thread,
				     struct thread_stack *ts, u64 timestamp,
				     u64 ref)
{
	struct thread_stack_entry *tse;
	int err;

	if (!ts->cnt)
		return 0;

	/* Pop trace end */
	tse = &ts->stack[ts->cnt - 1];
	if (tse->cp->sym == NULL && tse->cp->ip == 0) {
		err = thread_stack__call_return(thread, ts, --ts->cnt,
						timestamp, ref, false);
		if (err)
			return err;
	}

	return 0;
}