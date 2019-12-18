#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct socket {int /*<<< orphan*/  sk; } ;
struct smc_init_info {void* vlan_id; } ;
struct list_head {struct list_head* next; } ;
struct TYPE_2__ {struct list_head lower; } ;
struct net_device {int lower_level; TYPE_1__ adj_list; } ;
struct dst_entry {struct net_device* dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 scalar_t__ is_vlan_dev (struct net_device*) ; 
 scalar_t__ list_empty (struct list_head*) ; 
 scalar_t__ netdev_lower_get_next (struct net_device*,struct list_head**) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 struct dst_entry* sk_dst_get (int /*<<< orphan*/ ) ; 
 void* vlan_dev_vlan_id (struct net_device*) ; 

int smc_vlan_by_tcpsk(struct socket *clcsock, struct smc_init_info *ini)
{
	struct dst_entry *dst = sk_dst_get(clcsock->sk);
	struct net_device *ndev;
	int i, nest_lvl, rc = 0;

	ini->vlan_id = 0;
	if (!dst) {
		rc = -ENOTCONN;
		goto out;
	}
	if (!dst->dev) {
		rc = -ENODEV;
		goto out_rel;
	}

	ndev = dst->dev;
	if (is_vlan_dev(ndev)) {
		ini->vlan_id = vlan_dev_vlan_id(ndev);
		goto out_rel;
	}

	rtnl_lock();
	nest_lvl = ndev->lower_level;
	for (i = 0; i < nest_lvl; i++) {
		struct list_head *lower = &ndev->adj_list.lower;

		if (list_empty(lower))
			break;
		lower = lower->next;
		ndev = (struct net_device *)netdev_lower_get_next(ndev, &lower);
		if (is_vlan_dev(ndev)) {
			ini->vlan_id = vlan_dev_vlan_id(ndev);
			break;
		}
	}
	rtnl_unlock();

out_rel:
	dst_release(dst);
out:
	return rc;
}