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
struct net_device {int dummy; } ;
struct TYPE_2__ {struct Qdisc* qdisc; } ;
struct etf_sched_data {TYPE_1__ watchdog; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  etf_disable_offload (struct net_device*,struct etf_sched_data*) ; 
 struct net_device* qdisc_dev (struct Qdisc*) ; 
 struct etf_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_watchdog_cancel (TYPE_1__*) ; 

__attribute__((used)) static void etf_destroy(struct Qdisc *sch)
{
	struct etf_sched_data *q = qdisc_priv(sch);
	struct net_device *dev = qdisc_dev(sch);

	/* Only cancel watchdog if it's been initialized. */
	if (q->watchdog.qdisc == sch)
		qdisc_watchdog_cancel(&q->watchdog);

	etf_disable_offload(dev, q);
}