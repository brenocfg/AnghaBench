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
struct rtnl_link {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (struct rtnl_link**,int /*<<< orphan*/ *) ; 
 int RTM_NR_MSGTYPES ; 
 int RTNL_FAMILY_MAX ; 
 int /*<<< orphan*/  kfree (struct rtnl_link**) ; 
 int /*<<< orphan*/  kfree_rcu (struct rtnl_link*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct rtnl_link*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 struct rtnl_link*** rtnl_msg_handlers ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  synchronize_net () ; 

void rtnl_unregister_all(int protocol)
{
	struct rtnl_link **tab, *link;
	int msgindex;

	BUG_ON(protocol < 0 || protocol > RTNL_FAMILY_MAX);

	rtnl_lock();
	tab = rtnl_msg_handlers[protocol];
	if (!tab) {
		rtnl_unlock();
		return;
	}
	RCU_INIT_POINTER(rtnl_msg_handlers[protocol], NULL);
	for (msgindex = 0; msgindex < RTM_NR_MSGTYPES; msgindex++) {
		link = tab[msgindex];
		if (!link)
			continue;

		rcu_assign_pointer(tab[msgindex], NULL);
		kfree_rcu(link, rcu);
	}
	rtnl_unlock();

	synchronize_net();

	kfree(tab);
}