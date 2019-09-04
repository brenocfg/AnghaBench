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
struct net_bridge_mdb_htable {size_t ver; int /*<<< orphan*/  size; } ;
struct net_bridge_mdb_entry {int host_joined; int /*<<< orphan*/  rcu; int /*<<< orphan*/ * hlist; scalar_t__ ports; int /*<<< orphan*/  addr; int /*<<< orphan*/  timer; struct net_bridge* br; } ;
struct net_bridge {int /*<<< orphan*/  multicast_lock; int /*<<< orphan*/  mdb; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTM_DELMDB ; 
 int /*<<< orphan*/  br_mdb_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_multicast_free_group ; 
 int /*<<< orphan*/  call_rcu_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct net_bridge_mdb_entry* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 struct net_bridge_mdb_htable* mlock_dereference (int /*<<< orphan*/ ,struct net_bridge*) ; 
 struct net_bridge_mdb_entry* mp ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void br_multicast_group_expired(struct timer_list *t)
{
	struct net_bridge_mdb_entry *mp = from_timer(mp, t, timer);
	struct net_bridge *br = mp->br;
	struct net_bridge_mdb_htable *mdb;

	spin_lock(&br->multicast_lock);
	if (!netif_running(br->dev) || timer_pending(&mp->timer))
		goto out;

	mp->host_joined = false;
	br_mdb_notify(br->dev, NULL, &mp->addr, RTM_DELMDB, 0);

	if (mp->ports)
		goto out;

	mdb = mlock_dereference(br->mdb, br);

	hlist_del_rcu(&mp->hlist[mdb->ver]);
	mdb->size--;

	call_rcu_bh(&mp->rcu, br_multicast_free_group);

out:
	spin_unlock(&br->multicast_lock);
}