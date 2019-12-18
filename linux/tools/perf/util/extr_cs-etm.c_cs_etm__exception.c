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
struct cs_etm_traceid_queue {TYPE_1__* prev_packet; } ;
struct TYPE_2__ {scalar_t__ sample_type; int last_instr_taken_branch; } ;

/* Variables and functions */
 scalar_t__ CS_ETM_RANGE ; 

__attribute__((used)) static int cs_etm__exception(struct cs_etm_traceid_queue *tidq)
{
	/*
	 * When the exception packet is inserted, whether the last instruction
	 * in previous range packet is taken branch or not, we need to force
	 * to set 'prev_packet->last_instr_taken_branch' to true.  This ensures
	 * to generate branch sample for the instruction range before the
	 * exception is trapped to kernel or before the exception returning.
	 *
	 * The exception packet includes the dummy address values, so don't
	 * swap PACKET with PREV_PACKET.  This keeps PREV_PACKET to be useful
	 * for generating instruction and branch samples.
	 */
	if (tidq->prev_packet->sample_type == CS_ETM_RANGE)
		tidq->prev_packet->last_instr_taken_branch = true;

	return 0;
}