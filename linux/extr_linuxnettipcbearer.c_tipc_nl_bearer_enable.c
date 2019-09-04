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
struct sk_buff {int dummy; } ;
struct genl_info {int dummy; } ;

/* Variables and functions */
 int __tipc_nl_bearer_enable (struct sk_buff*,struct genl_info*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

int tipc_nl_bearer_enable(struct sk_buff *skb, struct genl_info *info)
{
	int err;

	rtnl_lock();
	err = __tipc_nl_bearer_enable(skb, info);
	rtnl_unlock();

	return err;
}