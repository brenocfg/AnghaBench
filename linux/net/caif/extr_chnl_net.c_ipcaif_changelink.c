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
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct chnl_net {int /*<<< orphan*/  conn_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  caif_netlink_parms (struct nlattr**,int /*<<< orphan*/ *) ; 
 struct chnl_net* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_state_change (struct net_device*) ; 

__attribute__((used)) static int ipcaif_changelink(struct net_device *dev, struct nlattr *tb[],
			     struct nlattr *data[],
			     struct netlink_ext_ack *extack)
{
	struct chnl_net *caifdev;
	ASSERT_RTNL();
	caifdev = netdev_priv(dev);
	caif_netlink_parms(data, &caifdev->conn_req);
	netdev_state_change(dev);
	return 0;
}