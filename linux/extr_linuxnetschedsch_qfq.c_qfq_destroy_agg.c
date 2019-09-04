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
struct qfq_sched {int wsum; int iwsum; struct qfq_aggregate* in_serv_agg; } ;
struct qfq_aggregate {scalar_t__ class_weight; int /*<<< orphan*/  nonfull_next; } ;

/* Variables and functions */
 int ONE_FP ; 
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct qfq_aggregate*) ; 
 struct qfq_aggregate* qfq_choose_next_agg (struct qfq_sched*) ; 

__attribute__((used)) static void qfq_destroy_agg(struct qfq_sched *q, struct qfq_aggregate *agg)
{
	hlist_del_init(&agg->nonfull_next);
	q->wsum -= agg->class_weight;
	if (q->wsum != 0)
		q->iwsum = ONE_FP / q->wsum;

	if (q->in_serv_agg == agg)
		q->in_serv_agg = qfq_choose_next_agg(q);
	kfree(agg);
}