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
typedef  int /*<<< orphan*/  u64 ;
struct cs_etm_traceid_queue {int /*<<< orphan*/  period_instructions; TYPE_3__* prev_packet; } ;
struct cs_etm_queue {TYPE_2__* etm; } ;
struct TYPE_6__ {scalar_t__ sample_type; } ;
struct TYPE_4__ {scalar_t__ last_branch; } ;
struct TYPE_5__ {TYPE_1__ synth_opts; } ;

/* Variables and functions */
 scalar_t__ CS_ETM_RANGE ; 
 int /*<<< orphan*/  cs_etm__last_executed_instr (TYPE_3__*) ; 
 int cs_etm__synth_instruction_sample (struct cs_etm_queue*,struct cs_etm_traceid_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs_etm__end_block(struct cs_etm_queue *etmq,
			     struct cs_etm_traceid_queue *tidq)
{
	int err;

	/*
	 * It has no new packet coming and 'etmq->packet' contains the stale
	 * packet which was set at the previous time with packets swapping;
	 * so skip to generate branch sample to avoid stale packet.
	 *
	 * For this case only flush branch stack and generate a last branch
	 * event for the branches left in the circular buffer at the end of
	 * the trace.
	 */
	if (etmq->etm->synth_opts.last_branch &&
	    tidq->prev_packet->sample_type == CS_ETM_RANGE) {
		/*
		 * Use the address of the end of the last reported execution
		 * range.
		 */
		u64 addr = cs_etm__last_executed_instr(tidq->prev_packet);

		err = cs_etm__synth_instruction_sample(
			etmq, tidq, addr,
			tidq->period_instructions);
		if (err)
			return err;

		tidq->period_instructions = 0;
	}

	return 0;
}