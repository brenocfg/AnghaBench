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
struct net_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_INFO (char*,int /*<<< orphan*/ ,int) ; 
 int dev_open (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static void ifup(struct net_device *netdev)
{
	int err;

	rtnl_lock();
	err = dev_open(netdev, NULL);
	if (err < 0)
		BT_INFO("iface %s cannot be opened (%d)", netdev->name, err);
	rtnl_unlock();
}