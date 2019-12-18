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
struct perf_sample {scalar_t__ flags; int /*<<< orphan*/  ip; } ;
struct intel_pt_queue {int dummy; } ;
struct intel_pt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_pt_prep_sample (struct intel_pt*,struct intel_pt_queue*,union perf_event*,struct perf_sample*) ; 

__attribute__((used)) static void intel_pt_prep_p_sample(struct intel_pt *pt,
				   struct intel_pt_queue *ptq,
				   union perf_event *event,
				   struct perf_sample *sample)
{
	intel_pt_prep_sample(pt, ptq, event, sample);

	/*
	 * Zero IP is used to mean "trace start" but that is not the case for
	 * power or PTWRITE events with no IP, so clear the flags.
	 */
	if (!sample->ip)
		sample->flags = 0;
}