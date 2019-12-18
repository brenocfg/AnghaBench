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
struct sk_buff {int /*<<< orphan*/  tstamp; } ;
struct etf_sched_data {int /*<<< orphan*/  watchdog; int /*<<< orphan*/  delta; } ;
struct Qdisc {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 struct sk_buff* etf_peek_timesortedlist (struct Qdisc*) ; 
 int /*<<< orphan*/  ktime_sub_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 
 struct etf_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_watchdog_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qdisc_watchdog_schedule_ns (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reset_watchdog(struct Qdisc *sch)
{
	struct etf_sched_data *q = qdisc_priv(sch);
	struct sk_buff *skb = etf_peek_timesortedlist(sch);
	ktime_t next;

	if (!skb) {
		qdisc_watchdog_cancel(&q->watchdog);
		return;
	}

	next = ktime_sub_ns(skb->tstamp, q->delta);
	qdisc_watchdog_schedule_ns(&q->watchdog, ktime_to_ns(next));
}