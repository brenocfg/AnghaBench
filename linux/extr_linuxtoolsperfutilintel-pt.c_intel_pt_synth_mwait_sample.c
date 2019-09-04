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
struct perf_synth_intel_mwait {int /*<<< orphan*/  payload; scalar_t__ reserved; } ;
struct perf_sample {int /*<<< orphan*/  raw_data; int /*<<< orphan*/  raw_size; int /*<<< orphan*/  stream_id; int /*<<< orphan*/  id; int /*<<< orphan*/  ip; } ;
struct intel_pt_queue {TYPE_1__* state; struct intel_pt* pt; union perf_event* event_buf; } ;
struct intel_pt {int /*<<< orphan*/  pwr_events_sample_type; int /*<<< orphan*/  mwait_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  mwait_payload; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int intel_pt_deliver_synth_event (struct intel_pt*,struct intel_pt_queue*,union perf_event*,struct perf_sample*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_pt_prep_p_sample (struct intel_pt*,struct intel_pt_queue*,union perf_event*,struct perf_sample*) ; 
 scalar_t__ intel_pt_skip_event (struct intel_pt*) ; 
 int /*<<< orphan*/  perf_synth__raw_data (struct perf_synth_intel_mwait*) ; 
 int /*<<< orphan*/  perf_synth__raw_size (struct perf_synth_intel_mwait) ; 

__attribute__((used)) static int intel_pt_synth_mwait_sample(struct intel_pt_queue *ptq)
{
	struct intel_pt *pt = ptq->pt;
	union perf_event *event = ptq->event_buf;
	struct perf_sample sample = { .ip = 0, };
	struct perf_synth_intel_mwait raw;

	if (intel_pt_skip_event(pt))
		return 0;

	intel_pt_prep_p_sample(pt, ptq, event, &sample);

	sample.id = ptq->pt->mwait_id;
	sample.stream_id = ptq->pt->mwait_id;

	raw.reserved = 0;
	raw.payload = cpu_to_le64(ptq->state->mwait_payload);

	sample.raw_size = perf_synth__raw_size(raw);
	sample.raw_data = perf_synth__raw_data(&raw);

	return intel_pt_deliver_synth_event(pt, ptq, event, &sample,
					    pt->pwr_events_sample_type);
}