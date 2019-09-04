#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u64 ;
struct qfq_sched {int /*<<< orphan*/ * bitmaps; int /*<<< orphan*/  V; int /*<<< orphan*/  oldV; } ;
struct qfq_group {scalar_t__ F; unsigned long long slot_shift; scalar_t__ S; int /*<<< orphan*/  index; } ;
struct qfq_aggregate {int /*<<< orphan*/  S; } ;

/* Variables and functions */
 size_t ER ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned int qfq_calc_state (struct qfq_sched*,struct qfq_group*) ; 
 struct qfq_group* qfq_ffs (struct qfq_sched*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfq_front_slot_remove (struct qfq_group*) ; 
 scalar_t__ qfq_round_down (int /*<<< orphan*/ ,unsigned long long) ; 
 struct qfq_aggregate* qfq_slot_head (struct qfq_group*) ; 
 struct qfq_aggregate* qfq_slot_scan (struct qfq_group*) ; 
 int /*<<< orphan*/  qfq_unblock_groups (struct qfq_sched*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  qfq_update_eligible (struct qfq_sched*) ; 

__attribute__((used)) static struct qfq_aggregate *qfq_choose_next_agg(struct qfq_sched *q)
{
	struct qfq_group *grp;
	struct qfq_aggregate *agg, *new_front_agg;
	u64 old_F;

	qfq_update_eligible(q);
	q->oldV = q->V;

	if (!q->bitmaps[ER])
		return NULL;

	grp = qfq_ffs(q, q->bitmaps[ER]);
	old_F = grp->F;

	agg = qfq_slot_head(grp);

	/* agg starts to be served, remove it from schedule */
	qfq_front_slot_remove(grp);

	new_front_agg = qfq_slot_scan(grp);

	if (new_front_agg == NULL) /* group is now inactive, remove from ER */
		__clear_bit(grp->index, &q->bitmaps[ER]);
	else {
		u64 roundedS = qfq_round_down(new_front_agg->S,
					      grp->slot_shift);
		unsigned int s;

		if (grp->S == roundedS)
			return agg;
		grp->S = roundedS;
		grp->F = roundedS + (2ULL << grp->slot_shift);
		__clear_bit(grp->index, &q->bitmaps[ER]);
		s = qfq_calc_state(q, grp);
		__set_bit(grp->index, &q->bitmaps[s]);
	}

	qfq_unblock_groups(q, grp->index, old_F);

	return agg;
}