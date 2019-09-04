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
struct skbprio_sched_data {int lowest_prio; scalar_t__ highest_prio; int /*<<< orphan*/  qstats; int /*<<< orphan*/ * qdiscs; } ;
struct TYPE_4__ {scalar_t__ qlen; } ;
struct TYPE_3__ {scalar_t__ backlog; } ;
struct Qdisc {TYPE_2__ q; TYPE_1__ qstats; } ;

/* Variables and functions */
 int SKBPRIO_MAX_PRIORITY ; 
 int /*<<< orphan*/  __skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct skbprio_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static void skbprio_reset(struct Qdisc *sch)
{
	struct skbprio_sched_data *q = qdisc_priv(sch);
	int prio;

	sch->qstats.backlog = 0;
	sch->q.qlen = 0;

	for (prio = 0; prio < SKBPRIO_MAX_PRIORITY; prio++)
		__skb_queue_purge(&q->qdiscs[prio]);

	memset(&q->qstats, 0, sizeof(q->qstats));
	q->highest_prio = 0;
	q->lowest_prio = SKBPRIO_MAX_PRIORITY - 1;
}