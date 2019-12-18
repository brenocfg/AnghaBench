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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct tc_gred_qopt {scalar_t__ limit; int /*<<< orphan*/  Scell_log; int /*<<< orphan*/  Plog; int /*<<< orphan*/  Wlog; int /*<<< orphan*/  qth_max; int /*<<< orphan*/  qth_min; } ;
struct netlink_ext_ack {int dummy; } ;
struct gred_sched_data {int red_flags; int DP; int prio; scalar_t__ limit; scalar_t__ backlog; int /*<<< orphan*/  vars; int /*<<< orphan*/  parms; } ;
struct gred_sched {int red_flags; struct gred_sched_data** tab; } ;
struct Qdisc {scalar_t__ limit; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int GRED_VQ_RED_FLAGS ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 struct gred_sched* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  red_check_params (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  red_end_of_idle_period (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  red_set_parms (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  red_set_vars (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int gred_change_vq(struct Qdisc *sch, int dp,
				 struct tc_gred_qopt *ctl, int prio,
				 u8 *stab, u32 max_P,
				 struct gred_sched_data **prealloc,
				 struct netlink_ext_ack *extack)
{
	struct gred_sched *table = qdisc_priv(sch);
	struct gred_sched_data *q = table->tab[dp];

	if (!red_check_params(ctl->qth_min, ctl->qth_max, ctl->Wlog)) {
		NL_SET_ERR_MSG_MOD(extack, "invalid RED parameters");
		return -EINVAL;
	}

	if (!q) {
		table->tab[dp] = q = *prealloc;
		*prealloc = NULL;
		if (!q)
			return -ENOMEM;
		q->red_flags = table->red_flags & GRED_VQ_RED_FLAGS;
	}

	q->DP = dp;
	q->prio = prio;
	if (ctl->limit > sch->limit)
		q->limit = sch->limit;
	else
		q->limit = ctl->limit;

	if (q->backlog == 0)
		red_end_of_idle_period(&q->vars);

	red_set_parms(&q->parms,
		      ctl->qth_min, ctl->qth_max, ctl->Wlog, ctl->Plog,
		      ctl->Scell_log, stab, max_P);
	red_set_vars(&q->vars);
	return 0;
}