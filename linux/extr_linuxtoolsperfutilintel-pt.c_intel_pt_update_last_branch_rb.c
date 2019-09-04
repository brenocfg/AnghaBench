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
struct intel_pt_state {int flags; int /*<<< orphan*/  to_ip; int /*<<< orphan*/  from_ip; } ;
struct intel_pt_queue {int last_branch_pos; TYPE_3__* pt; struct branch_stack* last_branch_rb; struct intel_pt_state* state; } ;
struct branch_stack {scalar_t__ nr; struct branch_entry* entries; } ;
struct TYPE_4__ {int abort; int in_tx; int /*<<< orphan*/  mispred; } ;
struct branch_entry {TYPE_1__ flags; int /*<<< orphan*/  to; int /*<<< orphan*/  from; } ;
struct TYPE_5__ {int last_branch_sz; } ;
struct TYPE_6__ {TYPE_2__ synth_opts; int /*<<< orphan*/  mispred_all; } ;

/* Variables and functions */
 int INTEL_PT_ABORT_TX ; 
 int INTEL_PT_IN_TX ; 

__attribute__((used)) static void intel_pt_update_last_branch_rb(struct intel_pt_queue *ptq)
{
	const struct intel_pt_state *state = ptq->state;
	struct branch_stack *bs = ptq->last_branch_rb;
	struct branch_entry *be;

	if (!ptq->last_branch_pos)
		ptq->last_branch_pos = ptq->pt->synth_opts.last_branch_sz;

	ptq->last_branch_pos -= 1;

	be              = &bs->entries[ptq->last_branch_pos];
	be->from        = state->from_ip;
	be->to          = state->to_ip;
	be->flags.abort = !!(state->flags & INTEL_PT_ABORT_TX);
	be->flags.in_tx = !!(state->flags & INTEL_PT_IN_TX);
	/* No support for mispredict */
	be->flags.mispred = ptq->pt->mispred_all;

	if (bs->nr < ptq->pt->synth_opts.last_branch_sz)
		bs->nr += 1;
}