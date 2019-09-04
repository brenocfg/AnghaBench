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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_seq; } ;
struct net {int dummy; } ;
struct fib_rules_ops {int /*<<< orphan*/  nlgroup; struct net* fro_net; } ;
struct fib_rule {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int fib_nl_fill_rule (struct sk_buff*,struct fib_rule*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct fib_rules_ops*) ; 
 int /*<<< orphan*/  fib_rule_nlmsg_size (struct fib_rules_ops*,struct fib_rule*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_notify (struct sk_buff*,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nlmsghdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_set_sk_err (struct net*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void notify_rule_change(int event, struct fib_rule *rule,
			       struct fib_rules_ops *ops, struct nlmsghdr *nlh,
			       u32 pid)
{
	struct net *net;
	struct sk_buff *skb;
	int err = -ENOBUFS;

	net = ops->fro_net;
	skb = nlmsg_new(fib_rule_nlmsg_size(ops, rule), GFP_KERNEL);
	if (skb == NULL)
		goto errout;

	err = fib_nl_fill_rule(skb, rule, pid, nlh->nlmsg_seq, event, 0, ops);
	if (err < 0) {
		/* -EMSGSIZE implies BUG in fib_rule_nlmsg_size() */
		WARN_ON(err == -EMSGSIZE);
		kfree_skb(skb);
		goto errout;
	}

	rtnl_notify(skb, net, pid, ops->nlgroup, nlh, GFP_KERNEL);
	return;
errout:
	if (err < 0)
		rtnl_set_sk_err(net, ops->nlgroup, err);
}