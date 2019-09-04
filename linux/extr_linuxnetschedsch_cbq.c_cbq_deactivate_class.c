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
struct cbq_sched_data {int activemask; struct cbq_class** active; } ;
struct cbq_class {int cpriority; struct cbq_class* next_alive; int /*<<< orphan*/  qdisc; } ;

/* Variables and functions */
 struct cbq_sched_data* qdisc_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cbq_deactivate_class(struct cbq_class *this)
{
	struct cbq_sched_data *q = qdisc_priv(this->qdisc);
	int prio = this->cpriority;
	struct cbq_class *cl;
	struct cbq_class *cl_prev = q->active[prio];

	do {
		cl = cl_prev->next_alive;
		if (cl == this) {
			cl_prev->next_alive = cl->next_alive;
			cl->next_alive = NULL;

			if (cl == q->active[prio]) {
				q->active[prio] = cl_prev;
				if (cl == q->active[prio]) {
					q->active[prio] = NULL;
					q->activemask &= ~(1<<prio);
					return;
				}
			}
			return;
		}
	} while ((cl_prev = cl) != q->active[prio]);
}