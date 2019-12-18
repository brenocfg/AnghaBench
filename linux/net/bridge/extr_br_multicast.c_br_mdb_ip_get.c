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
struct net_bridge_mdb_entry {int dummy; } ;
struct net_bridge {int /*<<< orphan*/  mdb_hash_tbl; int /*<<< orphan*/  multicast_lock; } ;
struct br_ip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  br_mdb_rht_params ; 
 int /*<<< orphan*/  lockdep_assert_held_once (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct net_bridge_mdb_entry* rhashtable_lookup (int /*<<< orphan*/ *,struct br_ip*,int /*<<< orphan*/ ) ; 

struct net_bridge_mdb_entry *br_mdb_ip_get(struct net_bridge *br,
					   struct br_ip *dst)
{
	struct net_bridge_mdb_entry *ent;

	lockdep_assert_held_once(&br->multicast_lock);

	rcu_read_lock();
	ent = rhashtable_lookup(&br->mdb_hash_tbl, dst, br_mdb_rht_params);
	rcu_read_unlock();

	return ent;
}