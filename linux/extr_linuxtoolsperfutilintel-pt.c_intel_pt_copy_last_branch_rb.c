#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct intel_pt_queue {size_t last_branch_pos; TYPE_2__* pt; struct branch_stack* last_branch; struct branch_stack* last_branch_rb; } ;
struct branch_stack {size_t nr; int /*<<< orphan*/ * entries; } ;
struct branch_entry {int dummy; } ;
struct TYPE_3__ {size_t last_branch_sz; } ;
struct TYPE_4__ {TYPE_1__ synth_opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void intel_pt_copy_last_branch_rb(struct intel_pt_queue *ptq)
{
	struct branch_stack *bs_src = ptq->last_branch_rb;
	struct branch_stack *bs_dst = ptq->last_branch;
	size_t nr = 0;

	bs_dst->nr = bs_src->nr;

	if (!bs_src->nr)
		return;

	nr = ptq->pt->synth_opts.last_branch_sz - ptq->last_branch_pos;
	memcpy(&bs_dst->entries[0],
	       &bs_src->entries[ptq->last_branch_pos],
	       sizeof(struct branch_entry) * nr);

	if (bs_src->nr >= ptq->pt->synth_opts.last_branch_sz) {
		memcpy(&bs_dst->entries[nr],
		       &bs_src->entries[0],
		       sizeof(struct branch_entry) * ptq->last_branch_pos);
	}
}