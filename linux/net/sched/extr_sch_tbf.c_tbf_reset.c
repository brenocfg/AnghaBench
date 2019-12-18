#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tbf_sched_data {int /*<<< orphan*/  watchdog; int /*<<< orphan*/  mtu; int /*<<< orphan*/  ptokens; int /*<<< orphan*/  buffer; int /*<<< orphan*/  tokens; int /*<<< orphan*/  t_c; int /*<<< orphan*/  qdisc; } ;
struct TYPE_4__ {scalar_t__ qlen; } ;
struct TYPE_3__ {scalar_t__ backlog; } ;
struct Qdisc {TYPE_2__ q; TYPE_1__ qstats; } ;

/* Variables and functions */
 int /*<<< orphan*/  ktime_get_ns () ; 
 struct tbf_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdisc_watchdog_cancel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tbf_reset(struct Qdisc *sch)
{
	struct tbf_sched_data *q = qdisc_priv(sch);

	qdisc_reset(q->qdisc);
	sch->qstats.backlog = 0;
	sch->q.qlen = 0;
	q->t_c = ktime_get_ns();
	q->tokens = q->buffer;
	q->ptokens = q->mtu;
	qdisc_watchdog_cancel(&q->watchdog);
}