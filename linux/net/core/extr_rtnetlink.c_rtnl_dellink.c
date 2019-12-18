#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct ifinfomsg {scalar_t__ ifi_index; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 size_t IFLA_GROUP ; 
 size_t IFLA_IFNAME ; 
 int /*<<< orphan*/  IFLA_MAX ; 
 size_t IFLA_TARGET_NETNSID ; 
 int IFNAMSIZ ; 
 scalar_t__ IS_ERR (struct net*) ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int PTR_ERR (struct net*) ; 
 struct net_device* __dev_get_by_index (struct net*,scalar_t__) ; 
 struct net_device* __dev_get_by_name (struct net*,char*) ; 
 int /*<<< orphan*/  ifla_policy ; 
 int nla_get_s32 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_strlcpy (char*,struct nlattr*,int) ; 
 struct ifinfomsg* nlmsg_data (struct nlmsghdr*) ; 
 int nlmsg_parse_deprecated (struct nlmsghdr*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  put_net (struct net*) ; 
 int rtnl_delete_link (struct net_device*) ; 
 int rtnl_ensure_unique_netns (struct nlattr**,struct netlink_ext_ack*,int) ; 
 struct net* rtnl_get_net_ns_capable (int /*<<< orphan*/ ,int) ; 
 int rtnl_group_dellink (struct net*,int /*<<< orphan*/ ) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtnl_dellink(struct sk_buff *skb, struct nlmsghdr *nlh,
			struct netlink_ext_ack *extack)
{
	struct net *net = sock_net(skb->sk);
	struct net *tgt_net = net;
	struct net_device *dev = NULL;
	struct ifinfomsg *ifm;
	char ifname[IFNAMSIZ];
	struct nlattr *tb[IFLA_MAX+1];
	int err;
	int netnsid = -1;

	err = nlmsg_parse_deprecated(nlh, sizeof(*ifm), tb, IFLA_MAX,
				     ifla_policy, extack);
	if (err < 0)
		return err;

	err = rtnl_ensure_unique_netns(tb, extack, true);
	if (err < 0)
		return err;

	if (tb[IFLA_IFNAME])
		nla_strlcpy(ifname, tb[IFLA_IFNAME], IFNAMSIZ);

	if (tb[IFLA_TARGET_NETNSID]) {
		netnsid = nla_get_s32(tb[IFLA_TARGET_NETNSID]);
		tgt_net = rtnl_get_net_ns_capable(NETLINK_CB(skb).sk, netnsid);
		if (IS_ERR(tgt_net))
			return PTR_ERR(tgt_net);
	}

	err = -EINVAL;
	ifm = nlmsg_data(nlh);
	if (ifm->ifi_index > 0)
		dev = __dev_get_by_index(tgt_net, ifm->ifi_index);
	else if (tb[IFLA_IFNAME])
		dev = __dev_get_by_name(tgt_net, ifname);
	else if (tb[IFLA_GROUP])
		err = rtnl_group_dellink(tgt_net, nla_get_u32(tb[IFLA_GROUP]));
	else
		goto out;

	if (!dev) {
		if (tb[IFLA_IFNAME] || ifm->ifi_index > 0)
			err = -ENODEV;

		goto out;
	}

	err = rtnl_delete_link(dev);

out:
	if (netnsid >= 0)
		put_net(tgt_net);

	return err;
}