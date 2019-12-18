#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pneigh_entry {int flags; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int NTF_ROUTER ; 
 struct pneigh_entry* __pneigh_lookup (TYPE_1__*,int /*<<< orphan*/ ,void const*,struct net_device*) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 TYPE_1__ nd_tbl ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pndisc_is_router(const void *pkey,
			    struct net_device *dev)
{
	struct pneigh_entry *n;
	int ret = -1;

	read_lock_bh(&nd_tbl.lock);
	n = __pneigh_lookup(&nd_tbl, dev_net(dev), pkey, dev);
	if (n)
		ret = !!(n->flags & NTF_ROUTER);
	read_unlock_bh(&nd_tbl.lock);

	return ret;
}