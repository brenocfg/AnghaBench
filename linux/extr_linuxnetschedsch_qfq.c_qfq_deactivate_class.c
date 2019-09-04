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
struct qfq_sched {int dummy; } ;
struct qfq_class {int /*<<< orphan*/  alist; struct qfq_aggregate* agg; } ;
struct qfq_aggregate {int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qfq_deactivate_agg (struct qfq_sched*,struct qfq_aggregate*) ; 

__attribute__((used)) static void qfq_deactivate_class(struct qfq_sched *q, struct qfq_class *cl)
{
	struct qfq_aggregate *agg = cl->agg;


	list_del(&cl->alist); /* remove from RR queue of the aggregate */
	if (list_empty(&agg->active)) /* agg is now inactive */
		qfq_deactivate_agg(q, agg);
}