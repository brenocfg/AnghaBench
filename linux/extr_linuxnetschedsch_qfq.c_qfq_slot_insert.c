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
typedef  int u64 ;
struct qfq_group {int S; int slot_shift; int front; int /*<<< orphan*/  full_slots; int /*<<< orphan*/ * slots; } ;
struct qfq_aggregate {int /*<<< orphan*/  next; int /*<<< orphan*/  F; int /*<<< orphan*/  S; } ;

/* Variables and functions */
 int QFQ_MAX_SLOTS ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void qfq_slot_insert(struct qfq_group *grp, struct qfq_aggregate *agg,
			    u64 roundedS)
{
	u64 slot = (roundedS - grp->S) >> grp->slot_shift;
	unsigned int i; /* slot index in the bucket list */

	if (unlikely(slot > QFQ_MAX_SLOTS - 2)) {
		u64 deltaS = roundedS - grp->S -
			((u64)(QFQ_MAX_SLOTS - 2)<<grp->slot_shift);
		agg->S -= deltaS;
		agg->F -= deltaS;
		slot = QFQ_MAX_SLOTS - 2;
	}

	i = (grp->front + slot) % QFQ_MAX_SLOTS;

	hlist_add_head(&agg->next, &grp->slots[i]);
	__set_bit(slot, &grp->full_slots);
}