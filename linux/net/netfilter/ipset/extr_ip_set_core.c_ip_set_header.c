#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_seq; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;
struct ip_set_net {int dummy; } ;
struct ip_set {int /*<<< orphan*/  revision; int /*<<< orphan*/  family; TYPE_1__* type; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  portid; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IPSET_ATTR_FAMILY ; 
 int /*<<< orphan*/  IPSET_ATTR_PROTOCOL ; 
 int /*<<< orphan*/  IPSET_ATTR_REVISION ; 
 size_t IPSET_ATTR_SETNAME ; 
 size_t IPSET_ATTR_TYPENAME ; 
 int /*<<< orphan*/  IPSET_CMD_HEADER ; 
 int IPSET_ERR_PROTOCOL ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 TYPE_2__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 struct ip_set* find_set (struct ip_set_net*,int /*<<< orphan*/ ) ; 
 struct ip_set_net* ip_set_pernet (struct net*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int netlink_unicast (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_data (struct nlattr const* const) ; 
 scalar_t__ nla_put_string (struct sk_buff*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  protocol (struct nlattr const* const*) ; 
 scalar_t__ protocol_min_failed (struct nlattr const* const*) ; 
 struct nlmsghdr* start_msg (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ip_set_header(struct net *net, struct sock *ctnl,
			 struct sk_buff *skb, const struct nlmsghdr *nlh,
			 const struct nlattr * const attr[],
			 struct netlink_ext_ack *extack)
{
	struct ip_set_net *inst = ip_set_pernet(net);
	const struct ip_set *set;
	struct sk_buff *skb2;
	struct nlmsghdr *nlh2;
	int ret = 0;

	if (unlikely(protocol_min_failed(attr) ||
		     !attr[IPSET_ATTR_SETNAME]))
		return -IPSET_ERR_PROTOCOL;

	set = find_set(inst, nla_data(attr[IPSET_ATTR_SETNAME]));
	if (!set)
		return -ENOENT;

	skb2 = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!skb2)
		return -ENOMEM;

	nlh2 = start_msg(skb2, NETLINK_CB(skb).portid, nlh->nlmsg_seq, 0,
			 IPSET_CMD_HEADER);
	if (!nlh2)
		goto nlmsg_failure;
	if (nla_put_u8(skb2, IPSET_ATTR_PROTOCOL, protocol(attr)) ||
	    nla_put_string(skb2, IPSET_ATTR_SETNAME, set->name) ||
	    nla_put_string(skb2, IPSET_ATTR_TYPENAME, set->type->name) ||
	    nla_put_u8(skb2, IPSET_ATTR_FAMILY, set->family) ||
	    nla_put_u8(skb2, IPSET_ATTR_REVISION, set->revision))
		goto nla_put_failure;
	nlmsg_end(skb2, nlh2);

	ret = netlink_unicast(ctnl, skb2, NETLINK_CB(skb).portid, MSG_DONTWAIT);
	if (ret < 0)
		return ret;

	return 0;

nla_put_failure:
	nlmsg_cancel(skb2, nlh2);
nlmsg_failure:
	kfree_skb(skb2);
	return -EMSGSIZE;
}