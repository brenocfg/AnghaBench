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
struct qfq_sched {struct qfq_aggregate* in_serv_agg; int /*<<< orphan*/  V; int /*<<< orphan*/  oldV; } ;
struct qfq_aggregate {int /*<<< orphan*/  S; int /*<<< orphan*/  budgetmax; int /*<<< orphan*/  budget; int /*<<< orphan*/  initial_budget; } ;
typedef  enum update_reason { ____Placeholder_update_reason } update_reason ;

/* Variables and functions */
 int /*<<< orphan*/  qfq_schedule_agg (struct qfq_sched*,struct qfq_aggregate*) ; 
 int /*<<< orphan*/  qfq_update_agg_ts (struct qfq_sched*,struct qfq_aggregate*,int) ; 

__attribute__((used)) static void qfq_activate_agg(struct qfq_sched *q, struct qfq_aggregate *agg,
			     enum update_reason reason)
{
	agg->initial_budget = agg->budget = agg->budgetmax; /* recharge budg. */

	qfq_update_agg_ts(q, agg, reason);
	if (q->in_serv_agg == NULL) { /* no aggr. in service or scheduled */
		q->in_serv_agg = agg; /* start serving this aggregate */
		 /* update V: to be in service, agg must be eligible */
		q->oldV = q->V = agg->S;
	} else if (agg != q->in_serv_agg)
		qfq_schedule_agg(q, agg);
}