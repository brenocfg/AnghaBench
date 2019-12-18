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
struct qfq_class {struct qfq_aggregate* agg; } ;
struct qfq_aggregate {int num_classes; } ;

/* Variables and functions */
 int /*<<< orphan*/  qfq_destroy_agg (struct qfq_sched*,struct qfq_aggregate*) ; 
 int /*<<< orphan*/  qfq_update_agg (struct qfq_sched*,struct qfq_aggregate*,int) ; 

__attribute__((used)) static void qfq_rm_from_agg(struct qfq_sched *q, struct qfq_class *cl)
{
	struct qfq_aggregate *agg = cl->agg;

	cl->agg = NULL;
	if (agg->num_classes == 1) { /* agg being emptied, destroy it */
		qfq_destroy_agg(q, agg);
		return;
	}
	qfq_update_agg(q, agg, agg->num_classes-1);
}