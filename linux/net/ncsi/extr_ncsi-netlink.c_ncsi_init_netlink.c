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

/* Variables and functions */
 int genl_register_family (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ncsi_genl_family ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 

int ncsi_init_netlink(struct net_device *dev)
{
	int rc;

	rc = genl_register_family(&ncsi_genl_family);
	if (rc)
		netdev_err(dev, "ncsi: failed to register netlink family\n");

	return rc;
}