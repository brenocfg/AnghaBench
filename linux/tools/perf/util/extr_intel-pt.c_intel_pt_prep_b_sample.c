#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  misc; } ;
struct TYPE_6__ {TYPE_2__ header; } ;
union perf_event {TYPE_3__ sample; } ;
struct perf_sample {int period; int /*<<< orphan*/  cpumode; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; int /*<<< orphan*/  ip; int /*<<< orphan*/  time; } ;
struct intel_pt_queue {int /*<<< orphan*/  flags; TYPE_1__* state; int /*<<< orphan*/  timestamp; } ;
struct intel_pt {int /*<<< orphan*/  tc; int /*<<< orphan*/  timeless_decoding; } ;
struct TYPE_4__ {int /*<<< orphan*/  to_ip; int /*<<< orphan*/  from_ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_pt_cpumode (struct intel_pt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_pt_prep_a_sample (struct intel_pt_queue*,union perf_event*,struct perf_sample*) ; 
 int /*<<< orphan*/  tsc_to_perf_time (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void intel_pt_prep_b_sample(struct intel_pt *pt,
				   struct intel_pt_queue *ptq,
				   union perf_event *event,
				   struct perf_sample *sample)
{
	intel_pt_prep_a_sample(ptq, event, sample);

	if (!pt->timeless_decoding)
		sample->time = tsc_to_perf_time(ptq->timestamp, &pt->tc);

	sample->ip = ptq->state->from_ip;
	sample->cpumode = intel_pt_cpumode(pt, sample->ip);
	sample->addr = ptq->state->to_ip;
	sample->period = 1;
	sample->flags = ptq->flags;

	event->sample.header.misc = sample->cpumode;
}