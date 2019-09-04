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
struct net_device {int /*<<< orphan*/  type; int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_IPGRE ; 
 int /*<<< orphan*/  ip_tunnel_setup (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipgre_net_id ; 
 int /*<<< orphan*/  ipgre_netdev_ops ; 

__attribute__((used)) static void ipgre_tunnel_setup(struct net_device *dev)
{
	dev->netdev_ops		= &ipgre_netdev_ops;
	dev->type		= ARPHRD_IPGRE;
	ip_tunnel_setup(dev, ipgre_net_id);
}