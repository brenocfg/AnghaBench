#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct evlist {int dummy; } ;
typedef  enum perf_call_graph_mode { ____Placeholder_perf_call_graph_mode } perf_call_graph_mode ;
struct TYPE_5__ {scalar_t__ mode; int record_mode; scalar_t__ min_percent; int /*<<< orphan*/  enabled; } ;
struct TYPE_4__ {int use_callchain; } ;

/* Variables and functions */
 int CALLCHAIN_DWARF ; 
 int CALLCHAIN_FP ; 
 int CALLCHAIN_LBR ; 
 int CALLCHAIN_NONE ; 
 scalar_t__ CHAIN_NONE ; 
 int EINVAL ; 
 int PERF_SAMPLE_BRANCH_STACK ; 
 int PERF_SAMPLE_CALLCHAIN ; 
 int PERF_SAMPLE_REGS_USER ; 
 int PERF_SAMPLE_STACK_USER ; 
 TYPE_2__ callchain_param ; 
 scalar_t__ callchain_register_param (TYPE_2__*) ; 
 int dwarf_callchain_users ; 
 int perf_evlist__combined_sample_type (struct evlist*) ; 
 TYPE_1__ symbol_conf ; 
 int /*<<< orphan*/  ui__error (char*) ; 

__attribute__((used)) static int setup_callchain(struct evlist *evlist)
{
	u64 sample_type = perf_evlist__combined_sample_type(evlist);
	enum perf_call_graph_mode mode = CALLCHAIN_NONE;

	if ((sample_type & PERF_SAMPLE_REGS_USER) &&
	    (sample_type & PERF_SAMPLE_STACK_USER)) {
		mode = CALLCHAIN_DWARF;
		dwarf_callchain_users = true;
	} else if (sample_type & PERF_SAMPLE_BRANCH_STACK)
		mode = CALLCHAIN_LBR;
	else if (sample_type & PERF_SAMPLE_CALLCHAIN)
		mode = CALLCHAIN_FP;

	if (!callchain_param.enabled &&
	    callchain_param.mode != CHAIN_NONE &&
	    mode != CALLCHAIN_NONE) {
		symbol_conf.use_callchain = true;
		if (callchain_register_param(&callchain_param) < 0) {
			ui__error("Can't register callchain params.\n");
			return -EINVAL;
		}
	}

	callchain_param.record_mode = mode;
	callchain_param.min_percent = 0;
	return 0;
}