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
typedef  union perf_event {int dummy; } perf_event ;
struct perf_sample {int /*<<< orphan*/  branch_stack; int /*<<< orphan*/  callchain; int /*<<< orphan*/  ip; } ;
struct intel_pt_queue {int /*<<< orphan*/  last_branch; int /*<<< orphan*/  chain; int /*<<< orphan*/  cpu; int /*<<< orphan*/  thread; } ;
struct TYPE_2__ {scalar_t__ last_branch; scalar_t__ callchain_sz; scalar_t__ callchain; } ;
struct intel_pt {TYPE_1__ synth_opts; int /*<<< orphan*/  kernel_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_pt_copy_last_branch_rb (struct intel_pt_queue*) ; 
 int /*<<< orphan*/  intel_pt_prep_b_sample (struct intel_pt*,struct intel_pt_queue*,union perf_event*,struct perf_sample*) ; 
 int /*<<< orphan*/  thread_stack__sample (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_pt_prep_sample(struct intel_pt *pt,
				 struct intel_pt_queue *ptq,
				 union perf_event *event,
				 struct perf_sample *sample)
{
	intel_pt_prep_b_sample(pt, ptq, event, sample);

	if (pt->synth_opts.callchain) {
		thread_stack__sample(ptq->thread, ptq->cpu, ptq->chain,
				     pt->synth_opts.callchain_sz + 1,
				     sample->ip, pt->kernel_start);
		sample->callchain = ptq->chain;
	}

	if (pt->synth_opts.last_branch) {
		intel_pt_copy_last_branch_rb(ptq);
		sample->branch_stack = ptq->last_branch;
	}
}