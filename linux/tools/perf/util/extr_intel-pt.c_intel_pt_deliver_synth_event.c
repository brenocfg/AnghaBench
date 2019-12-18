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
typedef  int /*<<< orphan*/  u64 ;
struct perf_sample {int dummy; } ;
struct intel_pt_queue {int dummy; } ;
struct TYPE_2__ {scalar_t__ last_branch; } ;
struct intel_pt {TYPE_1__ synth_opts; } ;

/* Variables and functions */
 int intel_pt_deliver_synth_b_event (struct intel_pt*,union perf_event*,struct perf_sample*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_pt_reset_last_branch_rb (struct intel_pt_queue*) ; 

__attribute__((used)) static inline int intel_pt_deliver_synth_event(struct intel_pt *pt,
					       struct intel_pt_queue *ptq,
					       union perf_event *event,
					       struct perf_sample *sample,
					       u64 type)
{
	int ret;

	ret = intel_pt_deliver_synth_b_event(pt, event, sample, type);

	if (pt->synth_opts.last_branch)
		intel_pt_reset_last_branch_rb(ptq);

	return ret;
}