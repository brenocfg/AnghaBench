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
struct net_bridge {int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  br_fdb_hash_fini (struct net_bridge*) ; 
 int /*<<< orphan*/  br_mdb_hash_fini (struct net_bridge*) ; 
 int /*<<< orphan*/  br_multicast_dev_del (struct net_bridge*) ; 
 int /*<<< orphan*/  br_multicast_uninit_stats (struct net_bridge*) ; 
 int /*<<< orphan*/  br_vlan_flush (struct net_bridge*) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 struct net_bridge* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void br_dev_uninit(struct net_device *dev)
{
	struct net_bridge *br = netdev_priv(dev);

	br_multicast_dev_del(br);
	br_multicast_uninit_stats(br);
	br_vlan_flush(br);
	br_mdb_hash_fini(br);
	br_fdb_hash_fini(br);
	free_percpu(br->stats);
}