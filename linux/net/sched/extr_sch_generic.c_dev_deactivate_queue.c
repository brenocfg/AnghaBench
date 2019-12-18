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
struct netdev_queue {int /*<<< orphan*/  qdisc; } ;
struct net_device {int dummy; } ;
struct Qdisc {int flags; int /*<<< orphan*/  seqlock; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int TCQ_F_BUILTIN ; 
 int TCQ_F_NOLOCK ; 
 int /*<<< orphan*/  __QDISC_STATE_DEACTIVATED ; 
 int /*<<< orphan*/ * qdisc_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_reset (struct Qdisc*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct Qdisc*) ; 
 struct Qdisc* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dev_deactivate_queue(struct net_device *dev,
				 struct netdev_queue *dev_queue,
				 void *_qdisc_default)
{
	struct Qdisc *qdisc_default = _qdisc_default;
	struct Qdisc *qdisc;

	qdisc = rtnl_dereference(dev_queue->qdisc);
	if (qdisc) {
		bool nolock = qdisc->flags & TCQ_F_NOLOCK;

		if (nolock)
			spin_lock_bh(&qdisc->seqlock);
		spin_lock_bh(qdisc_lock(qdisc));

		if (!(qdisc->flags & TCQ_F_BUILTIN))
			set_bit(__QDISC_STATE_DEACTIVATED, &qdisc->state);

		rcu_assign_pointer(dev_queue->qdisc, qdisc_default);
		qdisc_reset(qdisc);

		spin_unlock_bh(qdisc_lock(qdisc));
		if (nolock)
			spin_unlock_bh(&qdisc->seqlock);
	}
}