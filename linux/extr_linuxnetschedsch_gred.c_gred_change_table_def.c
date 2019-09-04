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
struct tc_gred_sopt {int DPs; scalar_t__ def_DP; scalar_t__ grio; int /*<<< orphan*/  flags; } ;
struct nlattr {int dummy; } ;
struct gred_sched {scalar_t__ DPs; scalar_t__ def; int /*<<< orphan*/ ** tab; int /*<<< orphan*/  red_flags; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_DPs ; 
 int /*<<< orphan*/  gred_destroy_vq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gred_disable_rio_mode (struct gred_sched*) ; 
 int /*<<< orphan*/  gred_disable_wred_mode (struct gred_sched*) ; 
 int /*<<< orphan*/  gred_enable_rio_mode (struct gred_sched*) ; 
 int /*<<< orphan*/  gred_enable_wred_mode (struct gred_sched*) ; 
 scalar_t__ gred_wred_mode_check (struct Qdisc*) ; 
 struct tc_gred_sopt* nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 struct gred_sched* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  sch_tree_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  sch_tree_unlock (struct Qdisc*) ; 

__attribute__((used)) static inline int gred_change_table_def(struct Qdisc *sch, struct nlattr *dps)
{
	struct gred_sched *table = qdisc_priv(sch);
	struct tc_gred_sopt *sopt;
	int i;

	if (!dps)
		return -EINVAL;

	sopt = nla_data(dps);

	if (sopt->DPs > MAX_DPs || sopt->DPs == 0 ||
	    sopt->def_DP >= sopt->DPs)
		return -EINVAL;

	sch_tree_lock(sch);
	table->DPs = sopt->DPs;
	table->def = sopt->def_DP;
	table->red_flags = sopt->flags;

	/*
	 * Every entry point to GRED is synchronized with the above code
	 * and the DP is checked against DPs, i.e. shadowed VQs can no
	 * longer be found so we can unlock right here.
	 */
	sch_tree_unlock(sch);

	if (sopt->grio) {
		gred_enable_rio_mode(table);
		gred_disable_wred_mode(table);
		if (gred_wred_mode_check(sch))
			gred_enable_wred_mode(table);
	} else {
		gred_disable_rio_mode(table);
		gred_disable_wred_mode(table);
	}

	for (i = table->DPs; i < MAX_DPs; i++) {
		if (table->tab[i]) {
			pr_warn("GRED: Warning: Destroying shadowed VQ 0x%x\n",
				i);
			gred_destroy_vq(table->tab[i]);
			table->tab[i] = NULL;
		}
	}

	return 0;
}