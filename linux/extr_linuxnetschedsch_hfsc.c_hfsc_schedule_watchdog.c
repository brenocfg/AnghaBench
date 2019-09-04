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
typedef  scalar_t__ u64 ;
struct TYPE_2__ {scalar_t__ cl_cfmin; } ;
struct hfsc_sched {int /*<<< orphan*/  watchdog; TYPE_1__ root; } ;
struct hfsc_class {scalar_t__ cl_e; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 struct hfsc_class* eltree_get_minel (struct hfsc_sched*) ; 
 struct hfsc_sched* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_watchdog_schedule (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void
hfsc_schedule_watchdog(struct Qdisc *sch)
{
	struct hfsc_sched *q = qdisc_priv(sch);
	struct hfsc_class *cl;
	u64 next_time = 0;

	cl = eltree_get_minel(q);
	if (cl)
		next_time = cl->cl_e;
	if (q->root.cl_cfmin != 0) {
		if (next_time == 0 || next_time > q->root.cl_cfmin)
			next_time = q->root.cl_cfmin;
	}
	if (next_time)
		qdisc_watchdog_schedule(&q->watchdog, next_time);
}