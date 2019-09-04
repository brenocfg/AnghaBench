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
struct gred_sched_data {scalar_t__ backlog; int /*<<< orphan*/  vars; } ;
struct gred_sched {int DPs; struct gred_sched_data** tab; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 struct gred_sched* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_reset_queue (struct Qdisc*) ; 
 int /*<<< orphan*/  red_restart (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gred_reset(struct Qdisc *sch)
{
	int i;
	struct gred_sched *t = qdisc_priv(sch);

	qdisc_reset_queue(sch);

	for (i = 0; i < t->DPs; i++) {
		struct gred_sched_data *q = t->tab[i];

		if (!q)
			continue;

		red_restart(&q->vars);
		q->backlog = 0;
	}
}