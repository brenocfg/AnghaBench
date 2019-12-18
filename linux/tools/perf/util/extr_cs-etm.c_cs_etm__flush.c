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
typedef  int /*<<< orphan*/  u64 ;
struct cs_etm_traceid_queue {struct cs_etm_packet* prev_packet; struct cs_etm_packet* packet; int /*<<< orphan*/  period_instructions; } ;
struct cs_etm_queue {struct cs_etm_auxtrace* etm; } ;
struct cs_etm_packet {scalar_t__ sample_type; } ;
struct TYPE_2__ {scalar_t__ last_branch; } ;
struct cs_etm_auxtrace {TYPE_1__ synth_opts; scalar_t__ sample_branches; } ;

/* Variables and functions */
 scalar_t__ CS_ETM_EMPTY ; 
 scalar_t__ CS_ETM_RANGE ; 
 int /*<<< orphan*/  cs_etm__last_executed_instr (struct cs_etm_packet*) ; 
 int cs_etm__synth_branch_sample (struct cs_etm_queue*,struct cs_etm_traceid_queue*) ; 
 int cs_etm__synth_instruction_sample (struct cs_etm_queue*,struct cs_etm_traceid_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs_etm__flush(struct cs_etm_queue *etmq,
			 struct cs_etm_traceid_queue *tidq)
{
	int err = 0;
	struct cs_etm_auxtrace *etm = etmq->etm;
	struct cs_etm_packet *tmp;

	/* Handle start tracing packet */
	if (tidq->prev_packet->sample_type == CS_ETM_EMPTY)
		goto swap_packet;

	if (etmq->etm->synth_opts.last_branch &&
	    tidq->prev_packet->sample_type == CS_ETM_RANGE) {
		/*
		 * Generate a last branch event for the branches left in the
		 * circular buffer at the end of the trace.
		 *
		 * Use the address of the end of the last reported execution
		 * range
		 */
		u64 addr = cs_etm__last_executed_instr(tidq->prev_packet);

		err = cs_etm__synth_instruction_sample(
			etmq, tidq, addr,
			tidq->period_instructions);
		if (err)
			return err;

		tidq->period_instructions = 0;

	}

	if (etm->sample_branches &&
	    tidq->prev_packet->sample_type == CS_ETM_RANGE) {
		err = cs_etm__synth_branch_sample(etmq, tidq);
		if (err)
			return err;
	}

swap_packet:
	if (etm->sample_branches || etm->synth_opts.last_branch) {
		/*
		 * Swap PACKET with PREV_PACKET: PACKET becomes PREV_PACKET for
		 * the next incoming packet.
		 */
		tmp = tidq->packet;
		tidq->packet = tidq->prev_packet;
		tidq->prev_packet = tmp;
	}

	return err;
}