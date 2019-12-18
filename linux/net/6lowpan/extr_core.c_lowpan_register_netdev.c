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
typedef  enum lowpan_lltypes { ____Placeholder_lowpan_lltypes } lowpan_lltypes ;

/* Variables and functions */
 int lowpan_register_netdevice (struct net_device*,int) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

int lowpan_register_netdev(struct net_device *dev,
			   enum lowpan_lltypes lltype)
{
	int ret;

	rtnl_lock();
	ret = lowpan_register_netdevice(dev, lltype);
	rtnl_unlock();
	return ret;
}