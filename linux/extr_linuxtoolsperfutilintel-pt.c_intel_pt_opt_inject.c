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
struct TYPE_2__ {int /*<<< orphan*/  inject; } ;
struct intel_pt {TYPE_1__ synth_opts; } ;

/* Variables and functions */
 int intel_pt_inject_event (union perf_event*,struct perf_sample*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int intel_pt_opt_inject(struct intel_pt *pt,
				      union perf_event *event,
				      struct perf_sample *sample, u64 type)
{
	if (!pt->synth_opts.inject)
		return 0;

	return intel_pt_inject_event(event, sample, type);
}