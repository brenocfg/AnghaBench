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
struct net_failover_info {int /*<<< orphan*/  standby_dev; int /*<<< orphan*/  primary_dev; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 struct net_failover_info* netdev_priv (struct net_device*) ; 
 struct net_device* rcu_dereference (int /*<<< orphan*/ ) ; 
 int vlan_vid_add (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlan_vid_del (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int net_failover_vlan_rx_add_vid(struct net_device *dev, __be16 proto,
					u16 vid)
{
	struct net_failover_info *nfo_info = netdev_priv(dev);
	struct net_device *primary_dev, *standby_dev;
	int ret = 0;

	primary_dev = rcu_dereference(nfo_info->primary_dev);
	if (primary_dev) {
		ret = vlan_vid_add(primary_dev, proto, vid);
		if (ret)
			return ret;
	}

	standby_dev = rcu_dereference(nfo_info->standby_dev);
	if (standby_dev) {
		ret = vlan_vid_add(standby_dev, proto, vid);
		if (ret)
			if (primary_dev)
				vlan_vid_del(primary_dev, proto, vid);
	}

	return ret;
}