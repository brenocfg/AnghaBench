#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int dp_cnt; int /*<<< orphan*/ * qstats; TYPE_2__* tab; int /*<<< orphan*/  dp_def; int /*<<< orphan*/  wred_on; int /*<<< orphan*/  grio_on; } ;
struct tc_gred_qopt_offload {int command; TYPE_3__ set; int /*<<< orphan*/  parent; int /*<<< orphan*/  handle; } ;
struct net_device {TYPE_4__* netdev_ops; } ;
struct TYPE_5__ {int qth_min; int Wlog; int qth_max; int /*<<< orphan*/  max_P; } ;
struct gred_sched_data {int /*<<< orphan*/  backlog; TYPE_1__ parms; int /*<<< orphan*/  prio; int /*<<< orphan*/  limit; } ;
struct gred_sched {unsigned int DPs; struct gred_sched_data** tab; int /*<<< orphan*/  def; } ;
struct Qdisc {int /*<<< orphan*/  qstats; int /*<<< orphan*/  parent; int /*<<< orphan*/  handle; } ;
typedef  enum tc_gred_command { ____Placeholder_tc_gred_command } tc_gred_command ;
struct TYPE_8__ {int /*<<< orphan*/  (* ndo_setup_tc ) (struct net_device*,int /*<<< orphan*/ ,struct tc_gred_qopt_offload*) ;} ;
struct TYPE_6__ {int present; int min; int max; int /*<<< orphan*/ * backlog; int /*<<< orphan*/  probability; int /*<<< orphan*/  is_harddrop; int /*<<< orphan*/  is_ecn; int /*<<< orphan*/  prio; int /*<<< orphan*/  limit; } ;

/* Variables and functions */
 int TC_GRED_REPLACE ; 
 int /*<<< orphan*/  TC_SETUP_QDISC_GRED ; 
 int /*<<< orphan*/  gred_rio_mode (struct gred_sched*) ; 
 int /*<<< orphan*/  gred_use_ecn (struct gred_sched_data*) ; 
 int /*<<< orphan*/  gred_use_harddrop (struct gred_sched_data*) ; 
 int /*<<< orphan*/  gred_wred_mode (struct gred_sched*) ; 
 struct net_device* qdisc_dev (struct Qdisc*) ; 
 struct gred_sched* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,int /*<<< orphan*/ ,struct tc_gred_qopt_offload*) ; 
 int /*<<< orphan*/  tc_can_offload (struct net_device*) ; 

__attribute__((used)) static void gred_offload(struct Qdisc *sch, enum tc_gred_command command)
{
	struct gred_sched *table = qdisc_priv(sch);
	struct net_device *dev = qdisc_dev(sch);
	struct tc_gred_qopt_offload opt = {
		.command	= command,
		.handle		= sch->handle,
		.parent		= sch->parent,
	};

	if (!tc_can_offload(dev) || !dev->netdev_ops->ndo_setup_tc)
		return;

	if (command == TC_GRED_REPLACE) {
		unsigned int i;

		opt.set.grio_on = gred_rio_mode(table);
		opt.set.wred_on = gred_wred_mode(table);
		opt.set.dp_cnt = table->DPs;
		opt.set.dp_def = table->def;

		for (i = 0; i < table->DPs; i++) {
			struct gred_sched_data *q = table->tab[i];

			if (!q)
				continue;
			opt.set.tab[i].present = true;
			opt.set.tab[i].limit = q->limit;
			opt.set.tab[i].prio = q->prio;
			opt.set.tab[i].min = q->parms.qth_min >> q->parms.Wlog;
			opt.set.tab[i].max = q->parms.qth_max >> q->parms.Wlog;
			opt.set.tab[i].is_ecn = gred_use_ecn(q);
			opt.set.tab[i].is_harddrop = gred_use_harddrop(q);
			opt.set.tab[i].probability = q->parms.max_P;
			opt.set.tab[i].backlog = &q->backlog;
		}
		opt.set.qstats = &sch->qstats;
	}

	dev->netdev_ops->ndo_setup_tc(dev, TC_SETUP_QDISC_GRED, &opt);
}