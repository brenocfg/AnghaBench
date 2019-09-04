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
typedef  union perf_event {int dummy; } perf_event ;
typedef  int /*<<< orphan*/  u64 ;
struct perf_sample {int dummy; } ;
struct intel_pt {int /*<<< orphan*/  session; } ;

/* Variables and functions */
 int intel_pt_opt_inject (struct intel_pt*,union perf_event*,struct perf_sample*,int /*<<< orphan*/ ) ; 
 int perf_session__deliver_synth_event (int /*<<< orphan*/ ,union perf_event*,struct perf_sample*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int intel_pt_deliver_synth_b_event(struct intel_pt *pt,
					  union perf_event *event,
					  struct perf_sample *sample, u64 type)
{
	int ret;

	ret = intel_pt_opt_inject(pt, event, sample, type);
	if (ret)
		return ret;

	ret = perf_session__deliver_synth_event(pt->session, event, sample);
	if (ret)
		pr_err("Intel PT: failed to deliver event, error %d\n", ret);

	return ret;
}