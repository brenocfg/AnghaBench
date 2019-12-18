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
struct netpoll_info {int /*<<< orphan*/  rcu; int /*<<< orphan*/  refcnt; } ;
struct netpoll {TYPE_1__* dev; } ;
struct net_device_ops {int /*<<< orphan*/  (* ndo_netpoll_cleanup ) (TYPE_1__*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  npinfo; struct net_device_ops* netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netpoll_srcu ; 
 int /*<<< orphan*/  rcu_cleanup_netpoll_info ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 struct netpoll_info* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  synchronize_srcu (int /*<<< orphan*/ *) ; 

void __netpoll_cleanup(struct netpoll *np)
{
	struct netpoll_info *npinfo;

	npinfo = rtnl_dereference(np->dev->npinfo);
	if (!npinfo)
		return;

	synchronize_srcu(&netpoll_srcu);

	if (refcount_dec_and_test(&npinfo->refcnt)) {
		const struct net_device_ops *ops;

		ops = np->dev->netdev_ops;
		if (ops->ndo_netpoll_cleanup)
			ops->ndo_netpoll_cleanup(np->dev);

		RCU_INIT_POINTER(np->dev->npinfo, NULL);
		call_rcu(&npinfo->rcu, rcu_cleanup_netpoll_info);
	} else
		RCU_INIT_POINTER(np->dev->npinfo, NULL);
}