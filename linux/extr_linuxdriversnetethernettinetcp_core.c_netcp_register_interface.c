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
struct netcp_intf {int netdev_registered; int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int register_netdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netcp_register_interface(struct netcp_intf *netcp)
{
	int ret;

	ret = register_netdev(netcp->ndev);
	if (!ret)
		netcp->netdev_registered = true;
	return ret;
}