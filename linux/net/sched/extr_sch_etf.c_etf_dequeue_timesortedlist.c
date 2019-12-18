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
struct etf_sched_data {int /*<<< orphan*/  delta; scalar_t__ deadline_mode; int /*<<< orphan*/  (* get_time ) () ;} ;
struct Qdisc {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 struct sk_buff* etf_peek_timesortedlist (struct Qdisc*) ; 
 scalar_t__ ktime_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_sub_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct etf_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  reset_watchdog (struct Qdisc*) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  timesortedlist_drop (struct Qdisc*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timesortedlist_remove (struct Qdisc*,struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *etf_dequeue_timesortedlist(struct Qdisc *sch)
{
	struct etf_sched_data *q = qdisc_priv(sch);
	struct sk_buff *skb;
	ktime_t now, next;

	skb = etf_peek_timesortedlist(sch);
	if (!skb)
		return NULL;

	now = q->get_time();

	/* Drop if packet has expired while in queue. */
	if (ktime_before(skb->tstamp, now)) {
		timesortedlist_drop(sch, skb, now);
		skb = NULL;
		goto out;
	}

	/* When in deadline mode, dequeue as soon as possible and change the
	 * txtime from deadline to (now + delta).
	 */
	if (q->deadline_mode) {
		timesortedlist_remove(sch, skb);
		skb->tstamp = now;
		goto out;
	}

	next = ktime_sub_ns(skb->tstamp, q->delta);

	/* Dequeue only if now is within the [txtime - delta, txtime] range. */
	if (ktime_after(now, next))
		timesortedlist_remove(sch, skb);
	else
		skb = NULL;

out:
	/* Now we may need to re-arm the qdisc watchdog for the next packet. */
	reset_watchdog(sch);

	return skb;
}