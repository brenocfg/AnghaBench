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
struct br_ip {int dummy; } ;
struct net_bridge_mdb_entry {int /*<<< orphan*/  mdb_node; int /*<<< orphan*/  rhnode; int /*<<< orphan*/  timer; struct br_ip addr; struct net_bridge* br; } ;
struct TYPE_2__ {int /*<<< orphan*/  nelems; } ;
struct net_bridge {scalar_t__ hash_max; int /*<<< orphan*/  mdb_list; TYPE_1__ mdb_hash_tbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BROPT_MULTICAST_ENABLED ; 
 int E2BIG ; 
 int ENOMEM ; 
 struct net_bridge_mdb_entry* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct net_bridge_mdb_entry* br_mdb_ip_get (struct net_bridge*,struct br_ip*) ; 
 int /*<<< orphan*/  br_mdb_rht_params ; 
 int /*<<< orphan*/  br_multicast_group_expired ; 
 int /*<<< orphan*/  br_opt_toggle (struct net_bridge*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct net_bridge_mdb_entry*) ; 
 struct net_bridge_mdb_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int rhashtable_lookup_insert_fast (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

struct net_bridge_mdb_entry *br_multicast_new_group(struct net_bridge *br,
						    struct br_ip *group)
{
	struct net_bridge_mdb_entry *mp;
	int err;

	mp = br_mdb_ip_get(br, group);
	if (mp)
		return mp;

	if (atomic_read(&br->mdb_hash_tbl.nelems) >= br->hash_max) {
		br_opt_toggle(br, BROPT_MULTICAST_ENABLED, false);
		return ERR_PTR(-E2BIG);
	}

	mp = kzalloc(sizeof(*mp), GFP_ATOMIC);
	if (unlikely(!mp))
		return ERR_PTR(-ENOMEM);

	mp->br = br;
	mp->addr = *group;
	timer_setup(&mp->timer, br_multicast_group_expired, 0);
	err = rhashtable_lookup_insert_fast(&br->mdb_hash_tbl, &mp->rhnode,
					    br_mdb_rht_params);
	if (err) {
		kfree(mp);
		mp = ERR_PTR(err);
	} else {
		hlist_add_head_rcu(&mp->mdb_node, &br->mdb_list);
	}

	return mp;
}