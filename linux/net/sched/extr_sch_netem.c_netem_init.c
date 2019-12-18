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
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct netem_sched_data {int /*<<< orphan*/  loss_model; int /*<<< orphan*/  watchdog; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLG_RANDOM ; 
 int EINVAL ; 
 int netem_change (struct Qdisc*,struct nlattr*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 struct netem_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_watchdog_init (int /*<<< orphan*/ *,struct Qdisc*) ; 

__attribute__((used)) static int netem_init(struct Qdisc *sch, struct nlattr *opt,
		      struct netlink_ext_ack *extack)
{
	struct netem_sched_data *q = qdisc_priv(sch);
	int ret;

	qdisc_watchdog_init(&q->watchdog, sch);

	if (!opt)
		return -EINVAL;

	q->loss_model = CLG_RANDOM;
	ret = netem_change(sch, opt, extack);
	if (ret)
		pr_info("netem: change failed\n");
	return ret;
}