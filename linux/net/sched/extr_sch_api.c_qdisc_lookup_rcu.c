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
typedef  int /*<<< orphan*/  u32 ;
struct netdev_queue {int /*<<< orphan*/  qdisc_sleeping; } ;
struct net_device {int /*<<< orphan*/  qdisc; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 struct netdev_queue* dev_ingress_queue_rcu (struct net_device*) ; 
 struct Qdisc* qdisc_match_from_root (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct Qdisc *qdisc_lookup_rcu(struct net_device *dev, u32 handle)
{
	struct netdev_queue *nq;
	struct Qdisc *q;

	if (!handle)
		return NULL;
	q = qdisc_match_from_root(dev->qdisc, handle);
	if (q)
		goto out;

	nq = dev_ingress_queue_rcu(dev);
	if (nq)
		q = qdisc_match_from_root(nq->qdisc_sleeping, handle);
out:
	return q;
}