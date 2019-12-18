#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {TYPE_1__ addr; } ;
struct net_bridge_fdb_entry {int /*<<< orphan*/  rcu; int /*<<< orphan*/  rhnode; int /*<<< orphan*/  fdb_node; TYPE_2__ key; scalar_t__ is_static; } ;
struct net_bridge {int /*<<< orphan*/  fdb_hash_tbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTM_DELNEIGH ; 
 int /*<<< orphan*/  br_fdb_rht_params ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdb_del_hw_addr (struct net_bridge*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdb_notify (struct net_bridge*,struct net_bridge_fdb_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fdb_rcu_free ; 
 int /*<<< orphan*/  hlist_del_init_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_fdb_delete (struct net_bridge*,struct net_bridge_fdb_entry*) ; 

__attribute__((used)) static void fdb_delete(struct net_bridge *br, struct net_bridge_fdb_entry *f,
		       bool swdev_notify)
{
	trace_fdb_delete(br, f);

	if (f->is_static)
		fdb_del_hw_addr(br, f->key.addr.addr);

	hlist_del_init_rcu(&f->fdb_node);
	rhashtable_remove_fast(&br->fdb_hash_tbl, &f->rhnode,
			       br_fdb_rht_params);
	fdb_notify(br, f, RTM_DELNEIGH, swdev_notify);
	call_rcu(&f->rcu, fdb_rcu_free);
}