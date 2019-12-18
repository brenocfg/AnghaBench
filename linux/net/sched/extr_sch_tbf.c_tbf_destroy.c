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
struct tbf_sched_data {int /*<<< orphan*/  qdisc; int /*<<< orphan*/  watchdog; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 struct tbf_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdisc_watchdog_cancel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tbf_destroy(struct Qdisc *sch)
{
	struct tbf_sched_data *q = qdisc_priv(sch);

	qdisc_watchdog_cancel(&q->watchdog);
	qdisc_put(q->qdisc);
}