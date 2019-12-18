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
struct thread {int dummy; } ;
struct symbol {int dummy; } ;
struct perf_sample {int dummy; } ;
struct evsel {int dummy; } ;
struct callchain_cursor {int dummy; } ;
struct addr_location {int dummy; } ;
struct TYPE_2__ {scalar_t__ order; } ;

/* Variables and functions */
 scalar_t__ ORDER_CALLEE ; 
 int /*<<< orphan*/  callchain_cursor_reset (struct callchain_cursor*) ; 
 TYPE_1__ callchain_param ; 
 int thread__resolve_callchain_sample (struct thread*,struct callchain_cursor*,struct evsel*,struct perf_sample*,struct symbol**,struct addr_location*,int) ; 
 int thread__resolve_callchain_unwind (struct thread*,struct callchain_cursor*,struct evsel*,struct perf_sample*,int) ; 

int thread__resolve_callchain(struct thread *thread,
			      struct callchain_cursor *cursor,
			      struct evsel *evsel,
			      struct perf_sample *sample,
			      struct symbol **parent,
			      struct addr_location *root_al,
			      int max_stack)
{
	int ret = 0;

	callchain_cursor_reset(cursor);

	if (callchain_param.order == ORDER_CALLEE) {
		ret = thread__resolve_callchain_sample(thread, cursor,
						       evsel, sample,
						       parent, root_al,
						       max_stack);
		if (ret)
			return ret;
		ret = thread__resolve_callchain_unwind(thread, cursor,
						       evsel, sample,
						       max_stack);
	} else {
		ret = thread__resolve_callchain_unwind(thread, cursor,
						       evsel, sample,
						       max_stack);
		if (ret)
			return ret;
		ret = thread__resolve_callchain_sample(thread, cursor,
						       evsel, sample,
						       parent, root_al,
						       max_stack);
	}

	return ret;
}