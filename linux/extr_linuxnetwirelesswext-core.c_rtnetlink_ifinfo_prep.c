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
struct nlmsghdr {int dummy; } ;
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  ifindex; int /*<<< orphan*/  type; } ;
struct ifinfomsg {scalar_t__ ifi_change; int /*<<< orphan*/  ifi_flags; int /*<<< orphan*/  ifi_index; int /*<<< orphan*/  ifi_type; scalar_t__ __ifi_pad; int /*<<< orphan*/  ifi_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  IFLA_IFNAME ; 
 int /*<<< orphan*/  RTM_NEWLINK ; 
 int /*<<< orphan*/  dev_get_flags (struct net_device*) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 struct ifinfomsg* nlmsg_data (struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nlmsghdr *rtnetlink_ifinfo_prep(struct net_device *dev,
					      struct sk_buff *skb)
{
	struct ifinfomsg *r;
	struct nlmsghdr  *nlh;

	nlh = nlmsg_put(skb, 0, 0, RTM_NEWLINK, sizeof(*r), 0);
	if (!nlh)
		return NULL;

	r = nlmsg_data(nlh);
	r->ifi_family = AF_UNSPEC;
	r->__ifi_pad = 0;
	r->ifi_type = dev->type;
	r->ifi_index = dev->ifindex;
	r->ifi_flags = dev_get_flags(dev);
	r->ifi_change = 0;	/* Wireless changes don't affect those flags */

	if (nla_put_string(skb, IFLA_IFNAME, dev->name))
		goto nla_put_failure;

	return nlh;
 nla_put_failure:
	nlmsg_cancel(skb, nlh);
	return NULL;
}