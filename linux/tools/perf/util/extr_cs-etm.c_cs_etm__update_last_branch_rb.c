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
struct cs_etm_traceid_queue {int last_branch_pos; int /*<<< orphan*/  packet; int /*<<< orphan*/  prev_packet; struct branch_stack* last_branch_rb; } ;
struct cs_etm_queue {TYPE_3__* etm; } ;
struct branch_stack {scalar_t__ nr; struct branch_entry* entries; } ;
struct TYPE_4__ {int predicted; scalar_t__ mispred; } ;
struct branch_entry {TYPE_1__ flags; int /*<<< orphan*/  to; int /*<<< orphan*/  from; } ;
struct TYPE_5__ {int last_branch_sz; } ;
struct TYPE_6__ {TYPE_2__ synth_opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  cs_etm__first_executed_instr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs_etm__last_executed_instr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cs_etm__update_last_branch_rb(struct cs_etm_queue *etmq,
					  struct cs_etm_traceid_queue *tidq)
{
	struct branch_stack *bs = tidq->last_branch_rb;
	struct branch_entry *be;

	/*
	 * The branches are recorded in a circular buffer in reverse
	 * chronological order: we start recording from the last element of the
	 * buffer down.  After writing the first element of the stack, move the
	 * insert position back to the end of the buffer.
	 */
	if (!tidq->last_branch_pos)
		tidq->last_branch_pos = etmq->etm->synth_opts.last_branch_sz;

	tidq->last_branch_pos -= 1;

	be       = &bs->entries[tidq->last_branch_pos];
	be->from = cs_etm__last_executed_instr(tidq->prev_packet);
	be->to	 = cs_etm__first_executed_instr(tidq->packet);
	/* No support for mispredict */
	be->flags.mispred = 0;
	be->flags.predicted = 1;

	/*
	 * Increment bs->nr until reaching the number of last branches asked by
	 * the user on the command line.
	 */
	if (bs->nr < etmq->etm->synth_opts.last_branch_sz)
		bs->nr += 1;
}