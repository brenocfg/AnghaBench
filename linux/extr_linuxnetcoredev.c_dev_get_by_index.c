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
struct net_device {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct net_device* dev_get_by_index_rcu (struct net*,int) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

struct net_device *dev_get_by_index(struct net *net, int ifindex)
{
	struct net_device *dev;

	rcu_read_lock();
	dev = dev_get_by_index_rcu(net, ifindex);
	if (dev)
		dev_hold(dev);
	rcu_read_unlock();
	return dev;
}