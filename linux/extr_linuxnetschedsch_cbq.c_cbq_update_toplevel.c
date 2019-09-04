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
struct cbq_sched_data {scalar_t__ toplevel; } ;
struct cbq_class {scalar_t__ level; scalar_t__ undertime; struct cbq_class* borrow; TYPE_2__* q; } ;
struct TYPE_3__ {int qlen; } ;
struct TYPE_4__ {TYPE_1__ q; } ;

/* Variables and functions */
 scalar_t__ PSCHED_PASTPERFECT ; 

__attribute__((used)) static inline void
cbq_update_toplevel(struct cbq_sched_data *q, struct cbq_class *cl,
		    struct cbq_class *borrowed)
{
	if (cl && q->toplevel >= borrowed->level) {
		if (cl->q->q.qlen > 1) {
			do {
				if (borrowed->undertime == PSCHED_PASTPERFECT) {
					q->toplevel = borrowed->level;
					return;
				}
			} while ((borrowed = borrowed->borrow) != NULL);
		}
#if 0
	/* It is not necessary now. Uncommenting it
	   will save CPU cycles, but decrease fairness.
	 */
		q->toplevel = TC_CBQ_MAXLEVEL;
#endif
	}
}