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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
struct cs_etm_traceid_queue {scalar_t__ period_instructions; struct cs_etm_packet* prev_packet; struct cs_etm_packet* packet; int /*<<< orphan*/  trace_chan_id; } ;
struct cs_etm_queue {struct cs_etm_auxtrace* etm; } ;
struct cs_etm_packet {scalar_t__ instr_count; scalar_t__ sample_type; scalar_t__ last_instr_taken_branch; } ;
struct TYPE_2__ {scalar_t__ last_branch; } ;
struct cs_etm_auxtrace {scalar_t__ instructions_sample_period; TYPE_1__ synth_opts; scalar_t__ sample_branches; scalar_t__ sample_instructions; } ;

/* Variables and functions */
 scalar_t__ CS_ETM_DISCONTINUITY ; 
 scalar_t__ CS_ETM_RANGE ; 
 scalar_t__ cs_etm__instr_addr (struct cs_etm_queue*,int /*<<< orphan*/ ,struct cs_etm_packet*,scalar_t__) ; 
 int cs_etm__synth_branch_sample (struct cs_etm_queue*,struct cs_etm_traceid_queue*) ; 
 int cs_etm__synth_instruction_sample (struct cs_etm_queue*,struct cs_etm_traceid_queue*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cs_etm__update_last_branch_rb (struct cs_etm_queue*,struct cs_etm_traceid_queue*) ; 

__attribute__((used)) static int cs_etm__sample(struct cs_etm_queue *etmq,
			  struct cs_etm_traceid_queue *tidq)
{
	struct cs_etm_auxtrace *etm = etmq->etm;
	struct cs_etm_packet *tmp;
	int ret;
	u8 trace_chan_id = tidq->trace_chan_id;
	u64 instrs_executed = tidq->packet->instr_count;

	tidq->period_instructions += instrs_executed;

	/*
	 * Record a branch when the last instruction in
	 * PREV_PACKET is a branch.
	 */
	if (etm->synth_opts.last_branch &&
	    tidq->prev_packet->sample_type == CS_ETM_RANGE &&
	    tidq->prev_packet->last_instr_taken_branch)
		cs_etm__update_last_branch_rb(etmq, tidq);

	if (etm->sample_instructions &&
	    tidq->period_instructions >= etm->instructions_sample_period) {
		/*
		 * Emit instruction sample periodically
		 * TODO: allow period to be defined in cycles and clock time
		 */

		/* Get number of instructions executed after the sample point */
		u64 instrs_over = tidq->period_instructions -
			etm->instructions_sample_period;

		/*
		 * Calculate the address of the sampled instruction (-1 as
		 * sample is reported as though instruction has just been
		 * executed, but PC has not advanced to next instruction)
		 */
		u64 offset = (instrs_executed - instrs_over - 1);
		u64 addr = cs_etm__instr_addr(etmq, trace_chan_id,
					      tidq->packet, offset);

		ret = cs_etm__synth_instruction_sample(
			etmq, tidq, addr, etm->instructions_sample_period);
		if (ret)
			return ret;

		/* Carry remaining instructions into next sample period */
		tidq->period_instructions = instrs_over;
	}

	if (etm->sample_branches) {
		bool generate_sample = false;

		/* Generate sample for tracing on packet */
		if (tidq->prev_packet->sample_type == CS_ETM_DISCONTINUITY)
			generate_sample = true;

		/* Generate sample for branch taken packet */
		if (tidq->prev_packet->sample_type == CS_ETM_RANGE &&
		    tidq->prev_packet->last_instr_taken_branch)
			generate_sample = true;

		if (generate_sample) {
			ret = cs_etm__synth_branch_sample(etmq, tidq);
			if (ret)
				return ret;
		}
	}

	if (etm->sample_branches || etm->synth_opts.last_branch) {
		/*
		 * Swap PACKET with PREV_PACKET: PACKET becomes PREV_PACKET for
		 * the next incoming packet.
		 */
		tmp = tidq->packet;
		tidq->packet = tidq->prev_packet;
		tidq->prev_packet = tmp;
	}

	return 0;
}