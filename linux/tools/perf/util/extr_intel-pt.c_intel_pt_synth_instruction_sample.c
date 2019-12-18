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
struct perf_sample {scalar_t__ insn_cnt; scalar_t__ cyc_cnt; scalar_t__ period; int /*<<< orphan*/  stream_id; int /*<<< orphan*/  id; int /*<<< orphan*/  ip; } ;
struct intel_pt_queue {TYPE_1__* state; scalar_t__ last_insn_cnt; scalar_t__ ipc_cyc_cnt; scalar_t__ last_in_cyc_cnt; scalar_t__ ipc_insn_cnt; scalar_t__ last_in_insn_cnt; struct intel_pt* pt; union perf_event* event_buf; } ;
struct intel_pt {int /*<<< orphan*/  instructions_sample_type; int /*<<< orphan*/  instructions_id; } ;
struct TYPE_2__ {scalar_t__ tot_insn_cnt; } ;

/* Variables and functions */
 int intel_pt_deliver_synth_event (struct intel_pt*,struct intel_pt_queue*,union perf_event*,struct perf_sample*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_pt_prep_sample (struct intel_pt*,struct intel_pt_queue*,union perf_event*,struct perf_sample*) ; 
 scalar_t__ intel_pt_skip_event (struct intel_pt*) ; 

__attribute__((used)) static int intel_pt_synth_instruction_sample(struct intel_pt_queue *ptq)
{
	struct intel_pt *pt = ptq->pt;
	union perf_event *event = ptq->event_buf;
	struct perf_sample sample = { .ip = 0, };

	if (intel_pt_skip_event(pt))
		return 0;

	intel_pt_prep_sample(pt, ptq, event, &sample);

	sample.id = ptq->pt->instructions_id;
	sample.stream_id = ptq->pt->instructions_id;
	sample.period = ptq->state->tot_insn_cnt - ptq->last_insn_cnt;

	sample.cyc_cnt = ptq->ipc_cyc_cnt - ptq->last_in_cyc_cnt;
	if (sample.cyc_cnt) {
		sample.insn_cnt = ptq->ipc_insn_cnt - ptq->last_in_insn_cnt;
		ptq->last_in_insn_cnt = ptq->ipc_insn_cnt;
		ptq->last_in_cyc_cnt = ptq->ipc_cyc_cnt;
	}

	ptq->last_insn_cnt = ptq->state->tot_insn_cnt;

	return intel_pt_deliver_synth_event(pt, ptq, event, &sample,
					    pt->instructions_sample_type);
}