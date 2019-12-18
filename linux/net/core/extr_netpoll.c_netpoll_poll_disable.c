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
struct net_device {int /*<<< orphan*/  npinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  netpoll_srcu ; 
 struct netpoll_info* srcu_dereference (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 

void netpoll_poll_disable(struct net_device *dev)
{
	struct netpoll_info *ni;
	int idx;
	might_sleep();
	idx = srcu_read_lock(&netpoll_srcu);
	ni = srcu_dereference(dev->npinfo, &netpoll_srcu);
	if (ni)
		down(&ni->dev_lock);
	srcu_read_unlock(&netpoll_srcu, idx);
}