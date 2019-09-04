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
struct htb_sched {int* row_mask; TYPE_2__* hlevel; } ;
struct htb_class {size_t level; } ;
struct TYPE_4__ {TYPE_1__* hprio; } ;
struct TYPE_3__ {int /*<<< orphan*/  row; } ;

/* Variables and functions */
 int ffz (int) ; 
 int /*<<< orphan*/  htb_add_to_id_tree (int /*<<< orphan*/ *,struct htb_class*,int) ; 

__attribute__((used)) static inline void htb_add_class_to_row(struct htb_sched *q,
					struct htb_class *cl, int mask)
{
	q->row_mask[cl->level] |= mask;
	while (mask) {
		int prio = ffz(~mask);
		mask &= ~(1 << prio);
		htb_add_to_id_tree(&q->hlevel[cl->level].hprio[prio].row, cl, prio);
	}
}