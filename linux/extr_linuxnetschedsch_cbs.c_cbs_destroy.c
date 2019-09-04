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
struct net_device {int dummy; } ;
struct cbs_sched_data {scalar_t__ qdisc; int /*<<< orphan*/  watchdog; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cbs_disable_offload (struct net_device*,struct cbs_sched_data*) ; 
 int /*<<< orphan*/  qdisc_destroy (scalar_t__) ; 
 struct net_device* qdisc_dev (struct Qdisc*) ; 
 struct cbs_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_watchdog_cancel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cbs_destroy(struct Qdisc *sch)
{
	struct cbs_sched_data *q = qdisc_priv(sch);
	struct net_device *dev = qdisc_dev(sch);

	qdisc_watchdog_cancel(&q->watchdog);

	cbs_disable_offload(dev, q);

	if (q->qdisc)
		qdisc_destroy(q->qdisc);
}