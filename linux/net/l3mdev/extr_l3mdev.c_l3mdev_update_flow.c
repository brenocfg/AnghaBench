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
struct flowi {int flowi_oif; int flowi_iif; int /*<<< orphan*/  flowi_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLOWI_FLAG_SKIP_NH_OIF ; 
 struct net_device* dev_get_by_index_rcu (struct net*,int) ; 
 int l3mdev_master_ifindex_rcu (struct net_device*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

void l3mdev_update_flow(struct net *net, struct flowi *fl)
{
	struct net_device *dev;
	int ifindex;

	rcu_read_lock();

	if (fl->flowi_oif) {
		dev = dev_get_by_index_rcu(net, fl->flowi_oif);
		if (dev) {
			ifindex = l3mdev_master_ifindex_rcu(dev);
			if (ifindex) {
				fl->flowi_oif = ifindex;
				fl->flowi_flags |= FLOWI_FLAG_SKIP_NH_OIF;
				goto out;
			}
		}
	}

	if (fl->flowi_iif) {
		dev = dev_get_by_index_rcu(net, fl->flowi_iif);
		if (dev) {
			ifindex = l3mdev_master_ifindex_rcu(dev);
			if (ifindex) {
				fl->flowi_iif = ifindex;
				fl->flowi_flags |= FLOWI_FLAG_SKIP_NH_OIF;
			}
		}
	}

out:
	rcu_read_unlock();
}