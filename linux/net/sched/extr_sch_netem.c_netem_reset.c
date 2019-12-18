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
struct netem_sched_data {int /*<<< orphan*/  watchdog; scalar_t__ qdisc; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 struct netem_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_reset (scalar_t__) ; 
 int /*<<< orphan*/  qdisc_reset_queue (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_watchdog_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tfifo_reset (struct Qdisc*) ; 

__attribute__((used)) static void netem_reset(struct Qdisc *sch)
{
	struct netem_sched_data *q = qdisc_priv(sch);

	qdisc_reset_queue(sch);
	tfifo_reset(sch);
	if (q->qdisc)
		qdisc_reset(q->qdisc);
	qdisc_watchdog_cancel(&q->watchdog);
}