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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  qlen; } ;
struct Qdisc {int flags; TYPE_1__ q; int /*<<< orphan*/  skb_bad_txq; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int TCQ_F_NOLOCK ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ qdisc_is_percpu_stats (struct Qdisc*) ; 
 int /*<<< orphan*/ * qdisc_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_qstats_backlog_inc (struct Qdisc*,struct sk_buff*) ; 
 int /*<<< orphan*/  qdisc_qstats_cpu_backlog_inc (struct Qdisc*,struct sk_buff*) ; 
 int /*<<< orphan*/  qdisc_qstats_cpu_qlen_inc (struct Qdisc*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void qdisc_enqueue_skb_bad_txq(struct Qdisc *q,
					     struct sk_buff *skb)
{
	spinlock_t *lock = NULL;

	if (q->flags & TCQ_F_NOLOCK) {
		lock = qdisc_lock(q);
		spin_lock(lock);
	}

	__skb_queue_tail(&q->skb_bad_txq, skb);

	if (qdisc_is_percpu_stats(q)) {
		qdisc_qstats_cpu_backlog_inc(q, skb);
		qdisc_qstats_cpu_qlen_inc(q);
	} else {
		qdisc_qstats_backlog_inc(q, skb);
		q->q.qlen++;
	}

	if (lock)
		spin_unlock(lock);
}