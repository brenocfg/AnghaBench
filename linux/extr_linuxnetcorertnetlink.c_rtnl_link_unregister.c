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
struct rtnl_link_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rtnl_link_unregister (struct rtnl_link_ops*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pernet_ops_rwsem ; 
 int /*<<< orphan*/  rtnl_lock_unregistering_all () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void rtnl_link_unregister(struct rtnl_link_ops *ops)
{
	/* Close the race with setup_net() and cleanup_net() */
	down_write(&pernet_ops_rwsem);
	rtnl_lock_unregistering_all();
	__rtnl_link_unregister(ops);
	rtnl_unlock();
	up_write(&pernet_ops_rwsem);
}