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
struct tbf_sched_data {int /*<<< orphan*/  t_c; int /*<<< orphan*/ * qdisc; int /*<<< orphan*/  watchdog; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 int /*<<< orphan*/  noop_qdisc ; 
 struct tbf_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_watchdog_init (int /*<<< orphan*/ *,struct Qdisc*) ; 
 int tbf_change (struct Qdisc*,struct nlattr*,struct netlink_ext_ack*) ; 

__attribute__((used)) static int tbf_init(struct Qdisc *sch, struct nlattr *opt,
		    struct netlink_ext_ack *extack)
{
	struct tbf_sched_data *q = qdisc_priv(sch);

	qdisc_watchdog_init(&q->watchdog, sch);
	q->qdisc = &noop_qdisc;

	if (!opt)
		return -EINVAL;

	q->t_c = ktime_get_ns();

	return tbf_change(sch, opt, extack);
}