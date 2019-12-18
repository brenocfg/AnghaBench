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
struct cs_etm_traceid_queue {size_t last_branch_pos; struct branch_stack* last_branch; struct branch_stack* last_branch_rb; } ;
struct cs_etm_queue {TYPE_2__* etm; } ;
struct branch_stack {size_t nr; int /*<<< orphan*/ * entries; } ;
struct branch_entry {int dummy; } ;
struct TYPE_3__ {size_t last_branch_sz; } ;
struct TYPE_4__ {TYPE_1__ synth_opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline
void cs_etm__copy_last_branch_rb(struct cs_etm_queue *etmq,
				 struct cs_etm_traceid_queue *tidq)
{
	struct branch_stack *bs_src = tidq->last_branch_rb;
	struct branch_stack *bs_dst = tidq->last_branch;
	size_t nr = 0;

	/*
	 * Set the number of records before early exit: ->nr is used to
	 * determine how many branches to copy from ->entries.
	 */
	bs_dst->nr = bs_src->nr;

	/*
	 * Early exit when there is nothing to copy.
	 */
	if (!bs_src->nr)
		return;

	/*
	 * As bs_src->entries is a circular buffer, we need to copy from it in
	 * two steps.  First, copy the branches from the most recently inserted
	 * branch ->last_branch_pos until the end of bs_src->entries buffer.
	 */
	nr = etmq->etm->synth_opts.last_branch_sz - tidq->last_branch_pos;
	memcpy(&bs_dst->entries[0],
	       &bs_src->entries[tidq->last_branch_pos],
	       sizeof(struct branch_entry) * nr);

	/*
	 * If we wrapped around at least once, the branches from the beginning
	 * of the bs_src->entries buffer and until the ->last_branch_pos element
	 * are older valid branches: copy them over.  The total number of
	 * branches copied over will be equal to the number of branches asked by
	 * the user in last_branch_sz.
	 */
	if (bs_src->nr >= etmq->etm->synth_opts.last_branch_sz) {
		memcpy(&bs_dst->entries[nr],
		       &bs_src->entries[0],
		       sizeof(struct branch_entry) * tidq->last_branch_pos);
	}
}