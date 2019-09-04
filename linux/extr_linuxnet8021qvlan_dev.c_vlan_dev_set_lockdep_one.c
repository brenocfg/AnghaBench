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
struct netdev_queue {int /*<<< orphan*/  _xmit_lock; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_set_class_and_subclass (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlan_netdev_xmit_lock_key ; 

__attribute__((used)) static void vlan_dev_set_lockdep_one(struct net_device *dev,
				     struct netdev_queue *txq,
				     void *_subclass)
{
	lockdep_set_class_and_subclass(&txq->_xmit_lock,
				       &vlan_netdev_xmit_lock_key,
				       *(int *)_subclass);
}