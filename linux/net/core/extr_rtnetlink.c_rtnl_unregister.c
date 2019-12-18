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
 int ENOENT ; 
 int RTNL_FAMILY_MAX ; 
 int /*<<< orphan*/  kfree_rcu (struct rtnl_link*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct rtnl_link*,int /*<<< orphan*/ *) ; 
 int rtm_msgindex (int) ; 
 struct rtnl_link** rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/ * rtnl_msg_handlers ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

int rtnl_unregister(int protocol, int msgtype)
{
	struct rtnl_link **tab, *link;
	int msgindex;

	BUG_ON(protocol < 0 || protocol > RTNL_FAMILY_MAX);
	msgindex = rtm_msgindex(msgtype);

	rtnl_lock();
	tab = rtnl_dereference(rtnl_msg_handlers[protocol]);
	if (!tab) {
		rtnl_unlock();
		return -ENOENT;
	}

	link = tab[msgindex];
	rcu_assign_pointer(tab[msgindex], NULL);
	rtnl_unlock();

	kfree_rcu(link, rcu);

	return 0;
}