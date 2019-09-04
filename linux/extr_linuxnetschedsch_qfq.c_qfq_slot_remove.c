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
typedef  unsigned int u64 ;
struct qfq_sched {int dummy; } ;
struct qfq_group {unsigned int slot_shift; unsigned int S; unsigned int front; int /*<<< orphan*/  full_slots; int /*<<< orphan*/ * slots; } ;
struct qfq_aggregate {int /*<<< orphan*/  next; int /*<<< orphan*/  S; } ;

/* Variables and functions */
 unsigned int QFQ_MAX_SLOTS ; 
 int /*<<< orphan*/  __clear_bit (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 scalar_t__ hlist_empty (int /*<<< orphan*/ *) ; 
 unsigned int qfq_round_down (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void qfq_slot_remove(struct qfq_sched *q, struct qfq_group *grp,
			    struct qfq_aggregate *agg)
{
	unsigned int i, offset;
	u64 roundedS;

	roundedS = qfq_round_down(agg->S, grp->slot_shift);
	offset = (roundedS - grp->S) >> grp->slot_shift;

	i = (grp->front + offset) % QFQ_MAX_SLOTS;

	hlist_del(&agg->next);
	if (hlist_empty(&grp->slots[i]))
		__clear_bit(offset, &grp->full_slots);
}