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
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mtu; } ;
struct codel_sched_data {TYPE_1__ params; int /*<<< orphan*/  stats; int /*<<< orphan*/  vars; } ;
struct Qdisc {int limit; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int DEFAULT_CODEL_LIMIT ; 
 int /*<<< orphan*/  TCQ_F_CAN_BYPASS ; 
 int codel_change (struct Qdisc*,struct nlattr*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  codel_params_init (TYPE_1__*) ; 
 int /*<<< orphan*/  codel_stats_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  codel_vars_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  psched_mtu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdisc_dev (struct Qdisc*) ; 
 struct codel_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static int codel_init(struct Qdisc *sch, struct nlattr *opt,
		      struct netlink_ext_ack *extack)
{
	struct codel_sched_data *q = qdisc_priv(sch);

	sch->limit = DEFAULT_CODEL_LIMIT;

	codel_params_init(&q->params);
	codel_vars_init(&q->vars);
	codel_stats_init(&q->stats);
	q->params.mtu = psched_mtu(qdisc_dev(sch));

	if (opt) {
		int err = codel_change(sch, opt, extack);

		if (err)
			return err;
	}

	if (sch->limit >= 1)
		sch->flags |= TCQ_F_CAN_BYPASS;
	else
		sch->flags &= ~TCQ_F_CAN_BYPASS;

	return 0;
}