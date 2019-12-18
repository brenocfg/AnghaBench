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
typedef  unsigned int u64 ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * first; } ;
struct TYPE_3__ {int /*<<< orphan*/ * first; } ;
struct fq_sched_data {int flow_plimit; int quantum; int initial_quantum; unsigned long flow_max_rate; unsigned long long time_next_delayed_flow; int rate_enable; int orphan_mask; int low_rate_threshold; unsigned int ce_threshold; int /*<<< orphan*/  fq_trees_log; int /*<<< orphan*/  watchdog; int /*<<< orphan*/ * fq_root; int /*<<< orphan*/  delayed; TYPE_2__ old_flows; TYPE_1__ new_flows; int /*<<< orphan*/  flow_refill_delay; } ;
struct Qdisc {int limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 scalar_t__ NSEC_PER_USEC ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int fq_change (struct Qdisc*,struct nlattr*,struct netlink_ext_ack*) ; 
 int fq_resize (struct Qdisc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ilog2 (int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int psched_mtu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdisc_dev (struct Qdisc*) ; 
 struct fq_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_watchdog_init_clockid (int /*<<< orphan*/ *,struct Qdisc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fq_init(struct Qdisc *sch, struct nlattr *opt,
		   struct netlink_ext_ack *extack)
{
	struct fq_sched_data *q = qdisc_priv(sch);
	int err;

	sch->limit		= 10000;
	q->flow_plimit		= 100;
	q->quantum		= 2 * psched_mtu(qdisc_dev(sch));
	q->initial_quantum	= 10 * psched_mtu(qdisc_dev(sch));
	q->flow_refill_delay	= msecs_to_jiffies(40);
	q->flow_max_rate	= ~0UL;
	q->time_next_delayed_flow = ~0ULL;
	q->rate_enable		= 1;
	q->new_flows.first	= NULL;
	q->old_flows.first	= NULL;
	q->delayed		= RB_ROOT;
	q->fq_root		= NULL;
	q->fq_trees_log		= ilog2(1024);
	q->orphan_mask		= 1024 - 1;
	q->low_rate_threshold	= 550000 / 8;

	/* Default ce_threshold of 4294 seconds */
	q->ce_threshold		= (u64)NSEC_PER_USEC * ~0U;

	qdisc_watchdog_init_clockid(&q->watchdog, sch, CLOCK_MONOTONIC);

	if (opt)
		err = fq_change(sch, opt, extack);
	else
		err = fq_resize(sch, q->fq_trees_log);

	return err;
}