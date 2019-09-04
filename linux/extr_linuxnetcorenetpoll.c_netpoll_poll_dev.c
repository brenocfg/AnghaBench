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
struct netpoll_info {int /*<<< orphan*/  dev_lock; } ;
struct net_device_ops {int /*<<< orphan*/  (* ndo_poll_controller ) (struct net_device*) ;} ;
struct net_device {struct net_device_ops* netdev_ops; int /*<<< orphan*/  npinfo; } ;

/* Variables and functions */
 scalar_t__ down_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  poll_napi (struct net_device*) ; 
 struct netpoll_info* rcu_dereference_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_completion_queue () ; 

void netpoll_poll_dev(struct net_device *dev)
{
	struct netpoll_info *ni = rcu_dereference_bh(dev->npinfo);
	const struct net_device_ops *ops;

	/* Don't do any rx activity if the dev_lock mutex is held
	 * the dev_open/close paths use this to block netpoll activity
	 * while changing device state
	 */
	if (!ni || down_trylock(&ni->dev_lock))
		return;

	if (!netif_running(dev)) {
		up(&ni->dev_lock);
		return;
	}

	ops = dev->netdev_ops;
	if (ops->ndo_poll_controller)
		ops->ndo_poll_controller(dev);

	poll_napi(dev);

	up(&ni->dev_lock);

	zap_completion_queue();
}