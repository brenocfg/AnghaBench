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
typedef  size_t u16 ;
struct multiq_sched_data {size_t bands; scalar_t__ curband; int /*<<< orphan*/ * queues; } ;
struct TYPE_2__ {scalar_t__ qlen; } ;
struct Qdisc {TYPE_1__ q; } ;

/* Variables and functions */
 struct multiq_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
multiq_reset(struct Qdisc *sch)
{
	u16 band;
	struct multiq_sched_data *q = qdisc_priv(sch);

	for (band = 0; band < q->bands; band++)
		qdisc_reset(q->queues[band]);
	sch->q.qlen = 0;
	q->curband = 0;
}