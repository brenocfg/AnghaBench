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
struct nlattr {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  IFLA_LINKINFO ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int rtnl_link_info_fill (struct sk_buff*,struct net_device const*) ; 
 int rtnl_link_slave_info_fill (struct sk_buff*,struct net_device const*) ; 

__attribute__((used)) static int rtnl_link_fill(struct sk_buff *skb, const struct net_device *dev)
{
	struct nlattr *linkinfo;
	int err = -EMSGSIZE;

	linkinfo = nla_nest_start_noflag(skb, IFLA_LINKINFO);
	if (linkinfo == NULL)
		goto out;

	err = rtnl_link_info_fill(skb, dev);
	if (err < 0)
		goto err_cancel_link;

	err = rtnl_link_slave_info_fill(skb, dev);
	if (err < 0)
		goto err_cancel_link;

	nla_nest_end(skb, linkinfo);
	return 0;

err_cancel_link:
	nla_nest_cancel(skb, linkinfo);
out:
	return err;
}