#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct perf_session {int /*<<< orphan*/  evlist; } ;
struct perf_script {struct perf_session* session; } ;
struct TYPE_4__ {int /*<<< orphan*/  record_mode; } ;
struct TYPE_3__ {scalar_t__ cumulate_callchain; scalar_t__ use_callchain; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALLCHAIN_DWARF ; 
 int /*<<< orphan*/  CALLCHAIN_FP ; 
 int /*<<< orphan*/  CALLCHAIN_LBR ; 
 int PERF_SAMPLE_BRANCH_STACK ; 
 int PERF_SAMPLE_REGS_USER ; 
 int PERF_SAMPLE_STACK_USER ; 
 TYPE_2__ callchain_param ; 
 int dwarf_callchain_users ; 
 int perf_evlist__combined_sample_type (int /*<<< orphan*/ ) ; 
 TYPE_1__ symbol_conf ; 

__attribute__((used)) static void script__setup_sample_type(struct perf_script *script)
{
	struct perf_session *session = script->session;
	u64 sample_type = perf_evlist__combined_sample_type(session->evlist);

	if (symbol_conf.use_callchain || symbol_conf.cumulate_callchain) {
		if ((sample_type & PERF_SAMPLE_REGS_USER) &&
		    (sample_type & PERF_SAMPLE_STACK_USER)) {
			callchain_param.record_mode = CALLCHAIN_DWARF;
			dwarf_callchain_users = true;
		} else if (sample_type & PERF_SAMPLE_BRANCH_STACK)
			callchain_param.record_mode = CALLCHAIN_LBR;
		else
			callchain_param.record_mode = CALLCHAIN_FP;
	}
}