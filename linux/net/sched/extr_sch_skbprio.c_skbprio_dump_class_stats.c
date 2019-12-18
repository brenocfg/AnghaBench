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
struct skbprio_sched_data {TYPE_1__* qstats; } ;
struct gnet_dump {int dummy; } ;
struct Qdisc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  qlen; } ;

/* Variables and functions */
 scalar_t__ gnet_stats_copy_queue (struct gnet_dump*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct skbprio_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static int skbprio_dump_class_stats(struct Qdisc *sch, unsigned long cl,
				   struct gnet_dump *d)
{
	struct skbprio_sched_data *q = qdisc_priv(sch);
	if (gnet_stats_copy_queue(d, NULL, &q->qstats[cl - 1],
		q->qstats[cl - 1].qlen) < 0)
		return -1;
	return 0;
}