#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct thread {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  size; } ;
struct TYPE_7__ {int /*<<< orphan*/  regs; } ;
struct perf_sample {TYPE_4__ user_stack; TYPE_3__ user_regs; } ;
struct TYPE_5__ {int sample_type; } ;
struct TYPE_6__ {TYPE_1__ attr; } ;
struct evsel {TYPE_2__ core; } ;
struct callchain_cursor {int dummy; } ;

/* Variables and functions */
 int PERF_SAMPLE_REGS_USER ; 
 int PERF_SAMPLE_STACK_USER ; 
 int unwind__get_entries (int /*<<< orphan*/ ,struct callchain_cursor*,struct thread*,struct perf_sample*,int) ; 
 int /*<<< orphan*/  unwind_entry ; 

__attribute__((used)) static int thread__resolve_callchain_unwind(struct thread *thread,
					    struct callchain_cursor *cursor,
					    struct evsel *evsel,
					    struct perf_sample *sample,
					    int max_stack)
{
	/* Can we do dwarf post unwind? */
	if (!((evsel->core.attr.sample_type & PERF_SAMPLE_REGS_USER) &&
	      (evsel->core.attr.sample_type & PERF_SAMPLE_STACK_USER)))
		return 0;

	/* Bail out if nothing was captured. */
	if ((!sample->user_regs.regs) ||
	    (!sample->user_stack.size))
		return 0;

	return unwind__get_entries(unwind_entry, cursor,
				   thread, sample, max_stack);
}