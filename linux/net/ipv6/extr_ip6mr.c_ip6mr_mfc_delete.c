#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mr_table {int /*<<< orphan*/  id; int /*<<< orphan*/  net; int /*<<< orphan*/  mfc_hash; } ;
struct TYPE_6__ {int /*<<< orphan*/  list; int /*<<< orphan*/  mnode; } ;
struct mfc6_cache {TYPE_3__ _c; } ;
struct TYPE_4__ {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  sin6_addr; } ;
struct mf6cctl {TYPE_1__ mf6cc_mcastgrp; TYPE_2__ mf6cc_origin; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  FIB_EVENT_ENTRY_DEL ; 
 int /*<<< orphan*/  RTM_DELROUTE ; 
 int /*<<< orphan*/  call_ip6mr_mfc_entry_notifiers (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mfc6_cache*,int /*<<< orphan*/ ) ; 
 struct mfc6_cache* ip6mr_cache_find_parent (struct mr_table*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ip6mr_rht_params ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mr6_netlink_event (struct mr_table*,struct mfc6_cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mr_cache_put (TYPE_3__*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  read_pnet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rhltable_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ip6mr_mfc_delete(struct mr_table *mrt, struct mf6cctl *mfc,
			    int parent)
{
	struct mfc6_cache *c;

	/* The entries are added/deleted only under RTNL */
	rcu_read_lock();
	c = ip6mr_cache_find_parent(mrt, &mfc->mf6cc_origin.sin6_addr,
				    &mfc->mf6cc_mcastgrp.sin6_addr, parent);
	rcu_read_unlock();
	if (!c)
		return -ENOENT;
	rhltable_remove(&mrt->mfc_hash, &c->_c.mnode, ip6mr_rht_params);
	list_del_rcu(&c->_c.list);

	call_ip6mr_mfc_entry_notifiers(read_pnet(&mrt->net),
				       FIB_EVENT_ENTRY_DEL, c, mrt->id);
	mr6_netlink_event(mrt, c, RTM_DELROUTE);
	mr_cache_put(&c->_c);
	return 0;
}