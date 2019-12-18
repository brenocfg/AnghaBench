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
struct timer_list {int dummy; } ;
struct net_bridge_mdb_entry {int /*<<< orphan*/  mdb_node; int /*<<< orphan*/  rhnode; scalar_t__ ports; int /*<<< orphan*/  timer; struct net_bridge* br; } ;
struct net_bridge {int /*<<< orphan*/  multicast_lock; int /*<<< orphan*/  mdb_hash_tbl; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  br_mdb_rht_params ; 
 int /*<<< orphan*/  br_multicast_host_leave (struct net_bridge_mdb_entry*,int) ; 
 struct net_bridge_mdb_entry* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_rcu (struct net_bridge_mdb_entry*,int /*<<< orphan*/ ) ; 
 struct net_bridge_mdb_entry* mp ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void br_multicast_group_expired(struct timer_list *t)
{
	struct net_bridge_mdb_entry *mp = from_timer(mp, t, timer);
	struct net_bridge *br = mp->br;

	spin_lock(&br->multicast_lock);
	if (!netif_running(br->dev) || timer_pending(&mp->timer))
		goto out;

	br_multicast_host_leave(mp, true);

	if (mp->ports)
		goto out;

	rhashtable_remove_fast(&br->mdb_hash_tbl, &mp->rhnode,
			       br_mdb_rht_params);
	hlist_del_rcu(&mp->mdb_node);

	kfree_rcu(mp, rcu);

out:
	spin_unlock(&br->multicast_lock);
}