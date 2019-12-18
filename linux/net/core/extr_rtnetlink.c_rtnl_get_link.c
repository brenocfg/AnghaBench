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
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 size_t PF_UNSPEC ; 
 struct rtnl_link** rcu_dereference_rtnl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rtnl_msg_handlers ; 

__attribute__((used)) static struct rtnl_link *rtnl_get_link(int protocol, int msgtype)
{
	struct rtnl_link **tab;

	if (protocol >= ARRAY_SIZE(rtnl_msg_handlers))
		protocol = PF_UNSPEC;

	tab = rcu_dereference_rtnl(rtnl_msg_handlers[protocol]);
	if (!tab)
		tab = rcu_dereference_rtnl(rtnl_msg_handlers[PF_UNSPEC]);

	return tab[msgtype];
}