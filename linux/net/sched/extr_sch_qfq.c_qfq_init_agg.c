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
typedef  void* u32 ;
struct qfq_sched {int /*<<< orphan*/  nonfull_aggs; } ;
struct qfq_aggregate {void* class_weight; void* lmax; int /*<<< orphan*/  nonfull_next; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qfq_init_agg(struct qfq_sched *q, struct qfq_aggregate *agg,
			 u32 lmax, u32 weight)
{
	INIT_LIST_HEAD(&agg->active);
	hlist_add_head(&agg->nonfull_next, &q->nonfull_aggs);

	agg->lmax = lmax;
	agg->class_weight = weight;
}