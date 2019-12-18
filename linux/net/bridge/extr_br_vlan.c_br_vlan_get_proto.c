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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct net_bridge {int /*<<< orphan*/  vlan_proto; } ;

/* Variables and functions */
 struct net_bridge* netdev_priv (struct net_device const*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

int br_vlan_get_proto(const struct net_device *dev, u16 *p_proto)
{
	struct net_bridge *br = netdev_priv(dev);

	*p_proto = ntohs(br->vlan_proto);

	return 0;
}