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
struct qdisc_walker {int stop; scalar_t__ count; scalar_t__ skip; scalar_t__ (* fn ) (struct Qdisc*,unsigned int,struct qdisc_walker*) ;} ;
struct cake_tin_data {TYPE_1__* flows; } ;
struct cake_sched_data {unsigned int tin_cnt; size_t* tin_order; struct cake_tin_data* tins; } ;
struct Qdisc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flowchain; } ;

/* Variables and functions */
 unsigned int CAKE_QUEUES ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 struct cake_sched_data* qdisc_priv (struct Qdisc*) ; 
 scalar_t__ stub1 (struct Qdisc*,unsigned int,struct qdisc_walker*) ; 

__attribute__((used)) static void cake_walk(struct Qdisc *sch, struct qdisc_walker *arg)
{
	struct cake_sched_data *q = qdisc_priv(sch);
	unsigned int i, j;

	if (arg->stop)
		return;

	for (i = 0; i < q->tin_cnt; i++) {
		struct cake_tin_data *b = &q->tins[q->tin_order[i]];

		for (j = 0; j < CAKE_QUEUES; j++) {
			if (list_empty(&b->flows[j].flowchain) ||
			    arg->count < arg->skip) {
				arg->count++;
				continue;
			}
			if (arg->fn(sch, i * CAKE_QUEUES + j + 1, arg) < 0) {
				arg->stop = 1;
				break;
			}
			arg->count++;
		}
	}
}