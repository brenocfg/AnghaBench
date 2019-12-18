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
struct prio_sched_data {int bands; int /*<<< orphan*/ * queues; int /*<<< orphan*/  block; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  prio_offload (struct Qdisc*,int /*<<< orphan*/ *) ; 
 struct prio_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_block_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
prio_destroy(struct Qdisc *sch)
{
	int prio;
	struct prio_sched_data *q = qdisc_priv(sch);

	tcf_block_put(q->block);
	prio_offload(sch, NULL);
	for (prio = 0; prio < q->bands; prio++)
		qdisc_put(q->queues[prio]);
}