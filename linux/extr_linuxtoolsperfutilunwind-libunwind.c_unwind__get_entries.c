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
typedef  int /*<<< orphan*/  unwind_entry_cb_t ;
struct thread {TYPE_1__* unwind_libunwind_ops; } ;
struct perf_sample {int dummy; } ;
struct TYPE_2__ {int (* get_entries ) (int /*<<< orphan*/ ,void*,struct thread*,struct perf_sample*,int) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,void*,struct thread*,struct perf_sample*,int) ; 

int unwind__get_entries(unwind_entry_cb_t cb, void *arg,
			 struct thread *thread,
			 struct perf_sample *data, int max_stack)
{
	if (thread->unwind_libunwind_ops)
		return thread->unwind_libunwind_ops->get_entries(cb, arg, thread, data, max_stack);
	return 0;
}