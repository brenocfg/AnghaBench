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
typedef  void* u64 ;
struct qfq_sched {void* V; int /*<<< orphan*/ * bitmaps; int /*<<< orphan*/ * in_serv_agg; } ;
struct qfq_group {unsigned long long slot_shift; void* S; int /*<<< orphan*/  index; void* F; scalar_t__ full_slots; } ;
struct qfq_aggregate {scalar_t__ F; void* S; struct qfq_group* grp; } ;

/* Variables and functions */
 size_t ER ; 
 size_t IB ; 
 size_t IR ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int /*<<< orphan*/ ,unsigned long long,unsigned long long,unsigned long long) ; 
 int qfq_calc_state (struct qfq_sched*,struct qfq_group*) ; 
 scalar_t__ qfq_gt (void*,void*) ; 
 void* qfq_round_down (void*,unsigned long long) ; 
 int /*<<< orphan*/  qfq_slot_insert (struct qfq_group*,struct qfq_aggregate*,void*) ; 
 int /*<<< orphan*/  qfq_slot_rotate (struct qfq_group*,void*) ; 

__attribute__((used)) static void qfq_schedule_agg(struct qfq_sched *q, struct qfq_aggregate *agg)
{
	struct qfq_group *grp = agg->grp;
	u64 roundedS;
	int s;

	roundedS = qfq_round_down(agg->S, grp->slot_shift);

	/*
	 * Insert agg in the correct bucket.
	 * If agg->S >= grp->S we don't need to adjust the
	 * bucket list and simply go to the insertion phase.
	 * Otherwise grp->S is decreasing, we must make room
	 * in the bucket list, and also recompute the group state.
	 * Finally, if there were no flows in this group and nobody
	 * was in ER make sure to adjust V.
	 */
	if (grp->full_slots) {
		if (!qfq_gt(grp->S, agg->S))
			goto skip_update;

		/* create a slot for this agg->S */
		qfq_slot_rotate(grp, roundedS);
		/* group was surely ineligible, remove */
		__clear_bit(grp->index, &q->bitmaps[IR]);
		__clear_bit(grp->index, &q->bitmaps[IB]);
	} else if (!q->bitmaps[ER] && qfq_gt(roundedS, q->V) &&
		   q->in_serv_agg == NULL)
		q->V = roundedS;

	grp->S = roundedS;
	grp->F = roundedS + (2ULL << grp->slot_shift);
	s = qfq_calc_state(q, grp);
	__set_bit(grp->index, &q->bitmaps[s]);

	pr_debug("qfq enqueue: new state %d %#lx S %lld F %lld V %lld\n",
		 s, q->bitmaps[s],
		 (unsigned long long) agg->S,
		 (unsigned long long) agg->F,
		 (unsigned long long) q->V);

skip_update:
	qfq_slot_insert(grp, agg, roundedS);
}