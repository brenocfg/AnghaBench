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
struct qfq_sched {unsigned long V; unsigned long min_slot_shift; unsigned long oldV; } ;

/* Variables and functions */
 int /*<<< orphan*/  EB ; 
 int /*<<< orphan*/  ER ; 
 int /*<<< orphan*/  IB ; 
 int /*<<< orphan*/  IR ; 
 int fls (unsigned long) ; 
 int /*<<< orphan*/  qfq_move_groups (struct qfq_sched*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qfq_make_eligible(struct qfq_sched *q)
{
	unsigned long vslot = q->V >> q->min_slot_shift;
	unsigned long old_vslot = q->oldV >> q->min_slot_shift;

	if (vslot != old_vslot) {
		unsigned long mask;
		int last_flip_pos = fls(vslot ^ old_vslot);

		if (last_flip_pos > 31) /* higher than the number of groups */
			mask = ~0UL;    /* make all groups eligible */
		else
			mask = (1UL << last_flip_pos) - 1;

		qfq_move_groups(q, mask, IR, ER);
		qfq_move_groups(q, mask, IB, EB);
	}
}