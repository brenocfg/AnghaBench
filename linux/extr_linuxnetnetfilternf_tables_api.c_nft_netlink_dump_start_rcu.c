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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct netlink_dump_control {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int netlink_dump_start (struct sock*,struct sk_buff*,struct nlmsghdr const*,struct netlink_dump_control*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_netlink_dump_start_rcu(struct sock *nlsk, struct sk_buff *skb,
				      const struct nlmsghdr *nlh,
				      struct netlink_dump_control *c)
{
	int err;

	if (!try_module_get(THIS_MODULE))
		return -EINVAL;

	rcu_read_unlock();
	err = netlink_dump_start(nlsk, skb, nlh, c);
	rcu_read_lock();
	module_put(THIS_MODULE);

	return err;
}