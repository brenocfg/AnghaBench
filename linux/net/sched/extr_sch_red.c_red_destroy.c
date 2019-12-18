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
struct red_sched_data {int /*<<< orphan*/  qdisc; int /*<<< orphan*/  adapt_timer; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct red_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  red_offload (struct Qdisc*,int) ; 

__attribute__((used)) static void red_destroy(struct Qdisc *sch)
{
	struct red_sched_data *q = qdisc_priv(sch);

	del_timer_sync(&q->adapt_timer);
	red_offload(sch, false);
	qdisc_put(q->qdisc);
}