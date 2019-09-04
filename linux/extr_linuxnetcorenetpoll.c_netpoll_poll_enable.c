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
 struct netpoll_info* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

void netpoll_poll_enable(struct net_device *dev)
{
	struct netpoll_info *ni;
	rcu_read_lock();
	ni = rcu_dereference(dev->npinfo);
	if (ni)
		up(&ni->dev_lock);
	rcu_read_unlock();
}