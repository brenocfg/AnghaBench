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
struct intel_pt_state {scalar_t__ tot_cyc_cnt; int type; scalar_t__ cbr; scalar_t__ to_ip; int /*<<< orphan*/  trace_nr; int /*<<< orphan*/  from_ip; int /*<<< orphan*/  tot_insn_cnt; } ;
struct intel_pt_queue {int have_sample; scalar_t__ ipc_cyc_cnt; scalar_t__ cbr_seen; int flags; int switch_state; int /*<<< orphan*/  sync_switch; int /*<<< orphan*/  cpu; int /*<<< orphan*/  thread; int /*<<< orphan*/  insn_len; struct intel_pt_state* state; int /*<<< orphan*/  ipc_insn_cnt; struct intel_pt* pt; } ;
struct TYPE_2__ {scalar_t__ last_branch; scalar_t__ thread_stack; scalar_t__ callchain; } ;
struct intel_pt {scalar_t__ ptss_ip; TYPE_1__ synth_opts; scalar_t__ sample_branches; scalar_t__ sample_ptwrites; scalar_t__ sample_transactions; scalar_t__ sample_instructions; scalar_t__ sample_pwr_events; scalar_t__ sample_pebs; } ;

/* Variables and functions */
 int INTEL_PT_BLK_ITEMS ; 
 int INTEL_PT_BRANCH ; 
 int INTEL_PT_EX_STOP ; 
 int INTEL_PT_INSTRUCTION ; 
 int INTEL_PT_MWAIT_OP ; 
 int INTEL_PT_PTW ; 
 int INTEL_PT_PWR_ENTRY ; 
 int INTEL_PT_PWR_EVT ; 
 int INTEL_PT_PWR_EXIT ; 
 int INTEL_PT_SS_EXPECTING_SWITCH_EVENT ; 
#define  INTEL_PT_SS_EXPECTING_SWITCH_IP 130 
#define  INTEL_PT_SS_NOT_TRACING 129 
 void* INTEL_PT_SS_TRACING ; 
#define  INTEL_PT_SS_UNKNOWN 128 
 int INTEL_PT_TRANSACTION ; 
 int PERF_IP_FLAG_CALL ; 
 scalar_t__ intel_pt_is_switch_ip (struct intel_pt_queue*,scalar_t__) ; 
 int intel_pt_next_tid (struct intel_pt*,struct intel_pt_queue*) ; 
 int intel_pt_synth_branch_sample (struct intel_pt_queue*) ; 
 int intel_pt_synth_cbr_sample (struct intel_pt_queue*) ; 
 int intel_pt_synth_exstop_sample (struct intel_pt_queue*) ; 
 int intel_pt_synth_instruction_sample (struct intel_pt_queue*) ; 
 int intel_pt_synth_mwait_sample (struct intel_pt_queue*) ; 
 int intel_pt_synth_pebs_sample (struct intel_pt_queue*) ; 
 int intel_pt_synth_ptwrite_sample (struct intel_pt_queue*) ; 
 int intel_pt_synth_pwre_sample (struct intel_pt_queue*) ; 
 int intel_pt_synth_pwrx_sample (struct intel_pt_queue*) ; 
 int intel_pt_synth_transaction_sample (struct intel_pt_queue*) ; 
 int /*<<< orphan*/  intel_pt_update_last_branch_rb (struct intel_pt_queue*) ; 
 int /*<<< orphan*/  thread_stack__event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_stack__set_trace_nr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_pt_sample(struct intel_pt_queue *ptq)
{
	const struct intel_pt_state *state = ptq->state;
	struct intel_pt *pt = ptq->pt;
	int err;

	if (!ptq->have_sample)
		return 0;

	ptq->have_sample = false;

	if (ptq->state->tot_cyc_cnt > ptq->ipc_cyc_cnt) {
		/*
		 * Cycle count and instruction count only go together to create
		 * a valid IPC ratio when the cycle count changes.
		 */
		ptq->ipc_insn_cnt = ptq->state->tot_insn_cnt;
		ptq->ipc_cyc_cnt = ptq->state->tot_cyc_cnt;
	}

	/*
	 * Do PEBS first to allow for the possibility that the PEBS timestamp
	 * precedes the current timestamp.
	 */
	if (pt->sample_pebs && state->type & INTEL_PT_BLK_ITEMS) {
		err = intel_pt_synth_pebs_sample(ptq);
		if (err)
			return err;
	}

	if (pt->sample_pwr_events) {
		if (ptq->state->cbr != ptq->cbr_seen) {
			err = intel_pt_synth_cbr_sample(ptq);
			if (err)
				return err;
		}
		if (state->type & INTEL_PT_PWR_EVT) {
			if (state->type & INTEL_PT_MWAIT_OP) {
				err = intel_pt_synth_mwait_sample(ptq);
				if (err)
					return err;
			}
			if (state->type & INTEL_PT_PWR_ENTRY) {
				err = intel_pt_synth_pwre_sample(ptq);
				if (err)
					return err;
			}
			if (state->type & INTEL_PT_EX_STOP) {
				err = intel_pt_synth_exstop_sample(ptq);
				if (err)
					return err;
			}
			if (state->type & INTEL_PT_PWR_EXIT) {
				err = intel_pt_synth_pwrx_sample(ptq);
				if (err)
					return err;
			}
		}
	}

	if (pt->sample_instructions && (state->type & INTEL_PT_INSTRUCTION)) {
		err = intel_pt_synth_instruction_sample(ptq);
		if (err)
			return err;
	}

	if (pt->sample_transactions && (state->type & INTEL_PT_TRANSACTION)) {
		err = intel_pt_synth_transaction_sample(ptq);
		if (err)
			return err;
	}

	if (pt->sample_ptwrites && (state->type & INTEL_PT_PTW)) {
		err = intel_pt_synth_ptwrite_sample(ptq);
		if (err)
			return err;
	}

	if (!(state->type & INTEL_PT_BRANCH))
		return 0;

	if (pt->synth_opts.callchain || pt->synth_opts.thread_stack)
		thread_stack__event(ptq->thread, ptq->cpu, ptq->flags, state->from_ip,
				    state->to_ip, ptq->insn_len,
				    state->trace_nr);
	else
		thread_stack__set_trace_nr(ptq->thread, ptq->cpu, state->trace_nr);

	if (pt->sample_branches) {
		err = intel_pt_synth_branch_sample(ptq);
		if (err)
			return err;
	}

	if (pt->synth_opts.last_branch)
		intel_pt_update_last_branch_rb(ptq);

	if (!ptq->sync_switch)
		return 0;

	if (intel_pt_is_switch_ip(ptq, state->to_ip)) {
		switch (ptq->switch_state) {
		case INTEL_PT_SS_NOT_TRACING:
		case INTEL_PT_SS_UNKNOWN:
		case INTEL_PT_SS_EXPECTING_SWITCH_IP:
			err = intel_pt_next_tid(pt, ptq);
			if (err)
				return err;
			ptq->switch_state = INTEL_PT_SS_TRACING;
			break;
		default:
			ptq->switch_state = INTEL_PT_SS_EXPECTING_SWITCH_EVENT;
			return 1;
		}
	} else if (!state->to_ip) {
		ptq->switch_state = INTEL_PT_SS_NOT_TRACING;
	} else if (ptq->switch_state == INTEL_PT_SS_NOT_TRACING) {
		ptq->switch_state = INTEL_PT_SS_UNKNOWN;
	} else if (ptq->switch_state == INTEL_PT_SS_UNKNOWN &&
		   state->to_ip == pt->ptss_ip &&
		   (ptq->flags & PERF_IP_FLAG_CALL)) {
		ptq->switch_state = INTEL_PT_SS_TRACING;
	}

	return 0;
}