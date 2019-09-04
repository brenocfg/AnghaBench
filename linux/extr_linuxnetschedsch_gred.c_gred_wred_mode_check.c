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
struct gred_sched_data {scalar_t__ prio; } ;
struct gred_sched {int DPs; struct gred_sched_data** tab; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 struct gred_sched* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static inline int gred_wred_mode_check(struct Qdisc *sch)
{
	struct gred_sched *table = qdisc_priv(sch);
	int i;

	/* Really ugly O(n^2) but shouldn't be necessary too frequent. */
	for (i = 0; i < table->DPs; i++) {
		struct gred_sched_data *q = table->tab[i];
		int n;

		if (q == NULL)
			continue;

		for (n = i + 1; n < table->DPs; n++)
			if (table->tab[n] && table->tab[n]->prio == q->prio)
				return 1;
	}

	return 0;
}