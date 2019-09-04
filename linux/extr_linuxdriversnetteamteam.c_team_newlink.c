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
struct net {int dummy; } ;

/* Variables and functions */
 size_t IFLA_ADDRESS ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int register_netdevice (struct net_device*) ; 

__attribute__((used)) static int team_newlink(struct net *src_net, struct net_device *dev,
			struct nlattr *tb[], struct nlattr *data[],
			struct netlink_ext_ack *extack)
{
	if (tb[IFLA_ADDRESS] == NULL)
		eth_hw_addr_random(dev);

	return register_netdevice(dev);
}