#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct htb_sched {int* row_mask; struct htb_level* hlevel; } ;
struct TYPE_2__ {int /*<<< orphan*/  rb_node; } ;
struct htb_prio {scalar_t__ ptr; TYPE_1__ row; } ;
struct htb_level {struct htb_prio* hprio; } ;
struct htb_class {size_t level; scalar_t__ node; } ;

/* Variables and functions */
 int ffz (int) ; 
 int /*<<< orphan*/  htb_next_rb_node (scalar_t__*) ; 
 int /*<<< orphan*/  htb_safe_rb_erase (scalar_t__,TYPE_1__*) ; 

__attribute__((used)) static inline void htb_remove_class_from_row(struct htb_sched *q,
						 struct htb_class *cl, int mask)
{
	int m = 0;
	struct htb_level *hlevel = &q->hlevel[cl->level];

	while (mask) {
		int prio = ffz(~mask);
		struct htb_prio *hprio = &hlevel->hprio[prio];

		mask &= ~(1 << prio);
		if (hprio->ptr == cl->node + prio)
			htb_next_rb_node(&hprio->ptr);

		htb_safe_rb_erase(cl->node + prio, &hprio->row);
		if (!hprio->row.rb_node)
			m |= 1 << prio;
	}
	q->row_mask[cl->level] &= ~m;
}