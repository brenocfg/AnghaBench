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
struct gred_sched {int DPs; scalar_t__* tab; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gred_destroy_vq (scalar_t__) ; 
 struct gred_sched* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static void gred_destroy(struct Qdisc *sch)
{
	struct gred_sched *table = qdisc_priv(sch);
	int i;

	for (i = 0; i < table->DPs; i++) {
		if (table->tab[i])
			gred_destroy_vq(table->tab[i]);
	}
}