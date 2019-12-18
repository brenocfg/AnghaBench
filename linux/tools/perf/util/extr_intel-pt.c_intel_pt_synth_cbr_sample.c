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
typedef  int u32 ;
typedef  int u16 ;
struct perf_synth_intel_cbr {int cbr; scalar_t__ reserved3; void* freq; void* flags; } ;
struct perf_sample {int /*<<< orphan*/  raw_data; int /*<<< orphan*/  raw_size; int /*<<< orphan*/  stream_id; int /*<<< orphan*/  id; int /*<<< orphan*/  ip; } ;
struct intel_pt_queue {TYPE_1__* state; struct intel_pt* pt; int /*<<< orphan*/  cbr_seen; union perf_event* event_buf; } ;
struct intel_pt {int max_non_turbo_ratio; int cbr2khz; int /*<<< orphan*/  pwr_events_sample_type; int /*<<< orphan*/  cbr_id; } ;
struct TYPE_2__ {scalar_t__ cbr_payload; int /*<<< orphan*/  cbr; } ;

/* Variables and functions */
 void* cpu_to_le32 (int) ; 
 int intel_pt_deliver_synth_event (struct intel_pt*,struct intel_pt_queue*,union perf_event*,struct perf_sample*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_pt_prep_p_sample (struct intel_pt*,struct intel_pt_queue*,union perf_event*,struct perf_sample*) ; 
 scalar_t__ intel_pt_skip_cbr_event (struct intel_pt*) ; 
 int /*<<< orphan*/  perf_synth__raw_data (struct perf_synth_intel_cbr*) ; 
 int /*<<< orphan*/  perf_synth__raw_size (struct perf_synth_intel_cbr) ; 

__attribute__((used)) static int intel_pt_synth_cbr_sample(struct intel_pt_queue *ptq)
{
	struct intel_pt *pt = ptq->pt;
	union perf_event *event = ptq->event_buf;
	struct perf_sample sample = { .ip = 0, };
	struct perf_synth_intel_cbr raw;
	u32 flags;

	if (intel_pt_skip_cbr_event(pt))
		return 0;

	ptq->cbr_seen = ptq->state->cbr;

	intel_pt_prep_p_sample(pt, ptq, event, &sample);

	sample.id = ptq->pt->cbr_id;
	sample.stream_id = ptq->pt->cbr_id;

	flags = (u16)ptq->state->cbr_payload | (pt->max_non_turbo_ratio << 16);
	raw.flags = cpu_to_le32(flags);
	raw.freq = cpu_to_le32(raw.cbr * pt->cbr2khz);
	raw.reserved3 = 0;

	sample.raw_size = perf_synth__raw_size(raw);
	sample.raw_data = perf_synth__raw_data(&raw);

	return intel_pt_deliver_synth_event(pt, ptq, event, &sample,
					    pt->pwr_events_sample_type);
}