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
struct qfq_group {size_t front; int /*<<< orphan*/  full_slots; int /*<<< orphan*/ * slots; } ;
struct qfq_aggregate {int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 scalar_t__ hlist_empty (int /*<<< orphan*/ *) ; 
 struct qfq_aggregate* qfq_slot_head (struct qfq_group*) ; 

__attribute__((used)) static void qfq_front_slot_remove(struct qfq_group *grp)
{
	struct qfq_aggregate *agg = qfq_slot_head(grp);

	BUG_ON(!agg);
	hlist_del(&agg->next);
	if (hlist_empty(&grp->slots[grp->front]))
		__clear_bit(0, &grp->full_slots);
}