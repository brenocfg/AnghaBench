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
struct tc_gred_sopt {int DPs; scalar_t__ def_DP; int flags; scalar_t__ grio; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct gred_sched {scalar_t__ DPs; scalar_t__ def; int red_flags; TYPE_1__** tab; } ;
struct Qdisc {int dummy; } ;
struct TYPE_2__ {int red_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int GRED_VQ_RED_FLAGS ; 
 int MAX_DPs ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  TC_GRED_REPLACE ; 
 int /*<<< orphan*/  gred_destroy_vq (TYPE_1__*) ; 
 int /*<<< orphan*/  gred_disable_rio_mode (struct gred_sched*) ; 
 int /*<<< orphan*/  gred_disable_wred_mode (struct gred_sched*) ; 
 int /*<<< orphan*/  gred_enable_rio_mode (struct gred_sched*) ; 
 int /*<<< orphan*/  gred_enable_wred_mode (struct gred_sched*) ; 
 int /*<<< orphan*/  gred_offload (struct Qdisc*,int /*<<< orphan*/ ) ; 
 scalar_t__ gred_per_vq_red_flags_used (struct gred_sched*) ; 
 scalar_t__ gred_wred_mode_check (struct Qdisc*) ; 
 struct tc_gred_sopt* nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 struct gred_sched* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  sch_tree_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  sch_tree_unlock (struct Qdisc*) ; 

__attribute__((used)) static int gred_change_table_def(struct Qdisc *sch, struct nlattr *dps,
				 struct netlink_ext_ack *extack)
{
	struct gred_sched *table = qdisc_priv(sch);
	struct tc_gred_sopt *sopt;
	bool red_flags_changed;
	int i;

	if (!dps)
		return -EINVAL;

	sopt = nla_data(dps);

	if (sopt->DPs > MAX_DPs) {
		NL_SET_ERR_MSG_MOD(extack, "number of virtual queues too high");
		return -EINVAL;
	}
	if (sopt->DPs == 0) {
		NL_SET_ERR_MSG_MOD(extack,
				   "number of virtual queues can't be 0");
		return -EINVAL;
	}
	if (sopt->def_DP >= sopt->DPs) {
		NL_SET_ERR_MSG_MOD(extack, "default virtual queue above virtual queue count");
		return -EINVAL;
	}
	if (sopt->flags && gred_per_vq_red_flags_used(table)) {
		NL_SET_ERR_MSG_MOD(extack, "can't set per-Qdisc RED flags when per-virtual queue flags are used");
		return -EINVAL;
	}

	sch_tree_lock(sch);
	table->DPs = sopt->DPs;
	table->def = sopt->def_DP;
	red_flags_changed = table->red_flags != sopt->flags;
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

	if (red_flags_changed)
		for (i = 0; i < table->DPs; i++)
			if (table->tab[i])
				table->tab[i]->red_flags =
					table->red_flags & GRED_VQ_RED_FLAGS;

	for (i = table->DPs; i < MAX_DPs; i++) {
		if (table->tab[i]) {
			pr_warn("GRED: Warning: Destroying shadowed VQ 0x%x\n",
				i);
			gred_destroy_vq(table->tab[i]);
			table->tab[i] = NULL;
		}
	}

	gred_offload(sch, TC_GRED_REPLACE);
	return 0;
}