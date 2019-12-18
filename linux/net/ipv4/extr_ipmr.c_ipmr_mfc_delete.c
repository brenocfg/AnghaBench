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
struct net {int dummy; } ;
struct mr_table {int /*<<< orphan*/  id; int /*<<< orphan*/  mfc_hash; int /*<<< orphan*/  net; } ;
struct TYPE_5__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct mfcctl {TYPE_2__ mfcc_mcastgrp; TYPE_1__ mfcc_origin; } ;
struct TYPE_6__ {int /*<<< orphan*/  list; int /*<<< orphan*/  mnode; } ;
struct mfc_cache {TYPE_3__ _c; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  FIB_EVENT_ENTRY_DEL ; 
 int /*<<< orphan*/  RTM_DELROUTE ; 
 int /*<<< orphan*/  call_ipmr_mfc_entry_notifiers (struct net*,int /*<<< orphan*/ ,struct mfc_cache*,int /*<<< orphan*/ ) ; 
 struct mfc_cache* ipmr_cache_find_parent (struct mr_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ipmr_rht_params ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mr_cache_put (TYPE_3__*) ; 
 int /*<<< orphan*/  mroute_netlink_event (struct mr_table*,struct mfc_cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct net* read_pnet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rhltable_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipmr_mfc_delete(struct mr_table *mrt, struct mfcctl *mfc, int parent)
{
	struct net *net = read_pnet(&mrt->net);
	struct mfc_cache *c;

	/* The entries are added/deleted only under RTNL */
	rcu_read_lock();
	c = ipmr_cache_find_parent(mrt, mfc->mfcc_origin.s_addr,
				   mfc->mfcc_mcastgrp.s_addr, parent);
	rcu_read_unlock();
	if (!c)
		return -ENOENT;
	rhltable_remove(&mrt->mfc_hash, &c->_c.mnode, ipmr_rht_params);
	list_del_rcu(&c->_c.list);
	call_ipmr_mfc_entry_notifiers(net, FIB_EVENT_ENTRY_DEL, c, mrt->id);
	mroute_netlink_event(mrt, c, RTM_DELROUTE);
	mr_cache_put(&c->_c);

	return 0;
}